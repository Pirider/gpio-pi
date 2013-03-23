import web
import RPi.GPIO as GPIO
urls = (
    '/', 'index',
    '/set/(.*)', 'setvalue', 
    '/get/(.*)', 'getvalue', 

)
vol_map = {
        'low'   : GPIO.LOW,
	'high'     : GPIO.HIGH,
}

class index:
    def GET(self):
	        return "Hello, world!"

    def POST(self):
        data = web.data() # you can get data use this method
	return "You just post date" + data;

class setvalue:
    def POST(self, value):
	GPIO.setmode(GPIO.BOARD)
	GPIO.setup(16, GPIO.OUT)
	GPIO.output(16, vol_map[value])
	return "Set success";

    def GET(self, value):
	GPIO.setmode(GPIO.BOARD)
	GPIO.setup(16, GPIO.OUT)
	GPIO.output(16, vol_map[value])
	return "Set success";

class getvalue:
    def POST(self, path):
	return "You just post date" + path;

if __name__ == "__main__":
    app = web.application(urls, globals())
    app.run()
