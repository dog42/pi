#!flask/bin/python

# use only for testing code is prone to injection attacks!


context = ('/etc/apache2/restcert/rest.crt','/etc/apache2/restcert/rest.key')

from flask import Flask
from flask import request
from flask import jsonify
import RPi.GPIO as GPIO

GPIO.setmode(GPIO.BCM)
GPIO.setup(17, GPIO.IN)
GPIO.setup(7, GPIO.OUT)

app = Flask(__name__)
app.config["JSON_SORT_KEYS"] = False

@app.route('/', methods=['POST'])
def do():
    print request.get_json()
    t = gettext()
    print t
    if t in ['/bla', '/blub']:
        input_value = GPIO.input(17)
    elif t in ['/foo' , '/bar']:
        GPIO.output(7, GPIO.HIGH)
    else:
        GPIO.output(7, GPIO.LOW)



    
    
    return jsonify({'status': 'OK', 'msg':'BAR'}), 200



if __name__ == '__main__':
    app.run(host='0.0.0.0',port=8443,debug=True,ssl_context=context )
    #app.run(host='127.0.0.1', debug=True, ssl_context=context)

GPIO.cleanup()