import serial

class Message:
    def __init__(self, temp, tempException, level, levelException):
        self.temp = temp
        self.tempException = tempException
        self.level = level
        self.levelException = levelException

    def getTemp(self):
        return self.temp
    
    def getTempException(self):
        return self.tempException
    
    def getLevel(self):
        return self.level

    def getLevelException(self):
        return self.levelException

class MessageHandler:
    def __init__(self):
        self.baudrate = 9600
        self.port = "COM4"
        self.device = serial.Serial(self.port, self.baudrate)

    def send(self, text):
        self.device.write(text)

    def read(self):
        strs = {"", "", "", ""}
        for i in range(4):
            strs[i] = self.device.read()

    def getPeriod(self):
        return self.device.read()