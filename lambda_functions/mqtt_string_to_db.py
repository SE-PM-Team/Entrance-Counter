import os
import boto3
from datetime import datetime, timedelta


def lambda_handler(event, context):
    try:
        # print(event)
        print("--------------------------------------")
        print("start")
        print(event)
        
        print("preparing data")
        input_item = prepare_data(event)
        print("input_data:", input_item)
        
        print("access ddb table")
        table = access_table()

        print("inputting item into table")
        response = table.put_item(Item=input_item)
        print(input_item["timestamp"], "PutItem succeeded:", response["ResponseMetadata"]["RequestId"])
        
        print("end")
        print("--------------------------------------")
    
    except Exception as e:
        print("Error:", e)
        # If you want to log the stack trace, you can uncomment the line below
        # print("Stack Trace:", traceback.format_exc())
        raise e
    
    
def prepare_data(event):
    payload = event['payload']
    counter_id, entered, exited = payload.split('-')

    # Get the utc+0 time
    current_time = datetime.now()
    # Add 1 hour to get the utc+1 time
    adjusted_time = current_time + timedelta(hours=1)
    # Convert the time to ISO format
    date_time = adjusted_time.isoformat()

    
    input_item = {
        "counter_id": counter_id,
        "entered": int(entered),
        "exited": int(exited),
        "timestamp": date_time,
    }

    return input_item
    

def access_table():
    dynamodb = boto3.resource(
        'dynamodb',
        region_name=os.getenv("REGION_NAME"),
        aws_access_key_id=os.getenv("ACCESS_KEY_ID"),
        aws_secret_access_key=os.getenv("SECRET_ACCESS_KEY")
    )
    
    table_name = os.getenv("TABLE_NAME")
    table = dynamodb.Table(table_name)
    
    return table
