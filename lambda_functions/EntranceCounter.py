import json
import os
import boto3

def lambda_handler(event, context):
	
	visit_count: int = 0

	# Prepare the DynamoDB client
	dynamodb = boto3.resource("dynamodb")
	table_name = os.environ["TABLE_NAME"]
	table = dynamodb.Table(table_name)
	print(table)
	primary_key = os.environ["PRIMARY_KEY"]
	key_value = "room"

	response = table.get_item(
	Key={primary_key: key_value},
	ProjectionExpression="#area_name, #total_result, #timestamp",
	ExpressionAttributeNames={
	"#area_name" : "area_name",
	"#total_result": "total_result",
	"#timestamp": "timestamp"
	}
	)



	# Check if the item was found
	if 'Item' in response:
		# Extract the column value from the DynamoDB response
		area_name = str(response['Item'].get("area_name", None))
		total_result = str(response['Item'].get("total_result", None))
		timestamp = str(response['Item'].get("timestamp", None))

		# Return the value in the API response
		responseObject = {}
		responseObject['statusCode'] = 200
		responseObject['area_name'] = json.dumps(area_name)
		responseObject['total_result'] = json.dumps(int(total_result))
		responseObject['timestamp'] = json.dumps(timestamp)
		
		
		return responseObject
		
	else:
		# Return a 404 Not Found response if the item was not found
		return {
		'statusCode': 404,
		'body': json.dumps({'error': 'Item not found'})}

	#4. Return the response object
	return responseObject
