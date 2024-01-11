import json
import os
import boto3
import urllib.request

print('Loading function')


def lambda_handler(event, context):
	print('------------------------')
	print(event)
	#1. Iterate over each record
	try:
		for record in event['Records']:
			#2. Handle event by type
			if record['eventName'] == 'INSERT':
				update_table(record)
		print('------------------------')
		return {'statusCode': 200}
		
	except Exception as e: 
		print(e)
		print('------------------------')
		return "Error"


def get_table():
	dynamodb = boto3.resource(
    	'dynamodb',
    	region_name=os.getenv("REGION_NAME"),
    	aws_access_key_id=os.getenv("ACCESS_KEY_ID"),
    	aws_secret_access_key=os.getenv("SECRET_ACCESS_KEY")
	)
	
	table = dynamodb.Table(os.getenv("TABLE_NAME"))
	
	return table

def get_old_values(ddb_table, primary_key_value):
	# Retrieve the item
	response = ddb_table.get_item(Key={'area_name': primary_key_value})
	
	# Check if the item was not found
	if 'Item' not in response:
		print("Item not found.")
		raise Error

	# Access the item from the response
	item = response['Item']
	old_total_entered = int(item["total_entered"])
	old_total_left = int(item["total_left"])
	print(old_total_entered, old_total_left)
	
	return old_total_entered, old_total_left
	

def get_new_values(record):
	# get newImage content
	newImage = record['dynamodb']['NewImage']
	
	#3 parse values
	timestamp = newImage['timestamp']['S']
	entered = int(newImage['entered']['N'])
	left = int(newImage['exited']['N'])
	
	return timestamp, entered, left
	
	
	
def prepare_update_data(ddb_table, primary_key_value, record):
	old_total_entered, old_total_left = get_old_values(ddb_table, primary_key_value)
	timestamp, new_total_entered, new_total_left = get_new_values(record)

	total_entered = old_total_entered + new_total_entered
	total_left = old_total_left + new_total_left
	total_result = total_entered - total_left

	# Specify the update expression and attribute values for multiple attributes
	update_expression = (
	    'SET #attr1_name = :attr1_value, '
	    '#attr2_name = :attr2_value, '
	    '#attr3_name = :attr3_value, '
	    '#attr4_name = :attr4_value'
	)
	
	expression_attribute_names = {
	    '#attr1_name': 'timestamp',
	    '#attr2_name': 'total_entered',
	    '#attr3_name': 'total_left',
	    '#attr4_name': 'total_result'
	}
	
	expression_attribute_values = {
	    ':attr1_value': timestamp,
	    ':attr2_value': total_entered,
	    ':attr3_value': total_left,
	    ':attr4_value': total_result
	}
	
	return update_expression, expression_attribute_names, expression_attribute_values
	
	
def	update_table(record):
	primary_key_value = "room"
	ddb_table = get_table() 
	
	print("Preparing update data")
	update_expression, expression_attribute_names, expression_attribute_values = prepare_update_data(ddb_table, primary_key_value, record)
	
	# Perform the update
	print("Performing table update")
	response = ddb_table.update_item(
    	Key={
        	'area_name': primary_key_value
    	},
    	UpdateExpression=update_expression,
    	ExpressionAttributeNames=expression_attribute_names,
    	ExpressionAttributeValues=expression_attribute_values,
    	ReturnValues='UPDATED_NEW'  # You can adjust this based on your needs
	)

	print("Finished table update")
	