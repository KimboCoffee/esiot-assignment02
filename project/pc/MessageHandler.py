import serial

class Message:
    def __init__(self, temp, level, exceptionType = 0):
        self.temp = temp
        self.level = level
        self.exceptionType = exceptionType

    def getTemp(self):
        return self.temp
    
    def getLevel(self):
        return self.level
    
    def getExceptionType(self):
        return self.exceptionType

class MessageHandler:
    def __init__(self):
        self.baudrate = 9600
        self.port = "COM4"
        self.device = serial.Serial(self.port, self.baudrate)

    def send(self, text):
        self.device.write(text)

    def read(self):
        #metodo che legge finché non trova "END", e poi restituisce un Message che contiene tutte le info
        self.device.read()
        return 0