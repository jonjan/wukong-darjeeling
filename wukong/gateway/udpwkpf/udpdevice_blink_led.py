from udpwkpf import WuClass, Device
import sys
import mraa

from twisted.protocols import basic
from twisted.internet import reactor, protocol

if __name__ == "__main__":
    class Button(WuClass):
        def __init__(self):
            self.ID = 1012
        
        def setup(self, obj, pin):
            button_gpio = mraa.Gpio(pin)
            print "Button init success"
            reactor.callLater(0.1, self.refresh, obj, pin, button_gpio)

        def refresh(self, obj, pin, button_gpio):
            current_value = button_gpio.read()
            obj.setProperty(0, current_value)
            print "Button pin: ", pin, ", value: ", current_value
            reactor.callLater(0.1, self.refresh, obj, pin, button_gpio)
            
    class Light_Actuator(WuClass):
        def __init__(self, pin):
            self.ID = 2001
            self.light_actuator_gpio = mraa.Gpio(pin)
            self.light_actuator_gpio.dir(mraa.DIR_OUT)
            print "Light Actuator init success"

        def update(self,obj,pID,val):
            if pID == 0:
                if val == True:
                    self.light_actuator_gpio.write(1)
                    print "Light Actuator On"
                else:
                    self.light_actuator_gpio.write(0)
                    print "Light Actuator Off"
            else:
                print "Light Actuator garbage"

    class MyDevice(Device):
        def __init__(self,addr,localaddr):
            Device.__init__(self,addr,localaddr)

        def init(self):
            Light_Actuator_Pin = 13
            m1 = Light_Actuator(Light_Actuator_Pin)
            self.addClass(m1,0)
            self.obj_light_actuator = self.addObject(m1.ID)

            Button_Pin = 5
            m2 = Button()
            self.addClass(m2,0)
            self.obj_button = self.addObject(m2.ID)
            self.obj_button.cls.setup(self.obj_button, Button_Pin)

    if len(sys.argv) <= 2:
        print 'python udpwkpf.py <ip> <port>'
        print '      <ip>: IP of the interface'
        print '      <port>: The unique port number in the interface'
        print ' ex. python <filename> <gateway ip> <local ip>:<any given port number>'
        print ' ex. python udpdevice_grove_kit_sample.py 192.168.4.7 127.0.0.1:3000'
        sys.exit(-1)

    d = MyDevice(sys.argv[1],sys.argv[2])
    reactor.run()
