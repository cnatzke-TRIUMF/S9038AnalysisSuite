#!/bin/python3

# system and web library 
import sys
import http.client

def send( message ):
    #webhook
    webhook_url = 

    # compile the form data 
    form_data = "------:::BOUNDARY:::\r\nContent-Disposition: form-data; name=\"content\"\r\n\r\n" + message + "\r\n------:::BOUNDARY:::--"

    # get the connection and make request
    connection = http.client.HTTPSConnection("discordapp.com")
    connection.request("POST", webhook_url, form_data, {
        'content-type': "multipart/form-data; boundary=----:::BOUNDARY:::",
        'cache-control': "no-cache",
        })

    # get response
    response = connection.getresponse()
    result = response.read()

    # return back to calling function with result
    return result.decode("utf-8")

# send the message and print the response
print( send( sys.argv[1] ) )
