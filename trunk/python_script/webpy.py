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

gpio_status = 'low'

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
	global gpio_status
        gpio_status = value
	return gpio_status;

    def GET(self, value):
	GPIO.setmode(GPIO.BOARD)
	GPIO.setup(16, GPIO.OUT)
	GPIO.output(16, vol_map[value])
	global gpio_status
	gpio_status = value
	return gpio_status;

class getvalue:
    def GET(self, value):
	return gpio_status;

if __name__ == "__main__":
    app = web.application(urls, globals())
    app.run()
