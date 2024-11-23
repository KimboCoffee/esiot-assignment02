import serial

class Message:
    def __init__(self, vals):
        self.period = vals[0]
        self.temp = vals[1]
        self.tempException = vals[2]
        self.level = vals[3]
        self.levelException = vals[4]

    def getPeriod(self):
        return self.period

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

    def send(self, val):
        self.device.write(val)

    def read(self):
        strs = ["", "", "", "", ""]
        for i in range(5):
            strs[i] = self.device.readline()
        return Message(strs)

    def getPeriod(self):
        return self.device.readline()
    
    def clearBuf(self):
        self.device.reset_input_buffer()