import json
import boto3


# arn copied from SNS topic "Room Status"
topic_arn = "arn:aws:sns:eu-central-1:892207807547:RoomStatus"


def lambda_handler(event, context):
    # TODO implement
    print(event)
    
    for record in event['Records']:
        new_image = record["dynamodb"]["NewImage"]
        old_image = record["dynamodb"]["OldImage"]
        
        limit = int(new_image["limit"]["N"])
        total = int(new_image["total_result"]["N"])
        old_total = int(old_image["total_result"]["N"])
        print(limit, total, old_total)
        
        if old_total < limit and total >= limit:
            message = f"Limit of {limit} has been reached. Please prevent/slow down entrance traffic."
            subject = f"Limit has been reached!"
            SNSResult = send_sns(message, subject)
            
            if SNSResult:
                print("Notification Sent..") 
                return SNSResult
            else:
                return False
            



def send_sns(message, subject):
    try:
        client = boto3.client("sns")
        result = client.publish(TopicArn=topic_arn, Message=message, Subject=subject)
        if result['ResponseMetadata']['HTTPStatusCode'] == 200:
            print(result)
            print("Notification sent successfully..!!!")
            return True
        
        return False
        
    except Exception as e:
        print("Error occured while publish notifications and error is : ", e)
        return True
