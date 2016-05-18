from udpwkpf import WuClass, Device
import sys
from udpwkpf_io_interface import *
from twisted.internet import reactor

Light_Actuator_Pin = 7

if __name__ == "__main__":
    class Light_Actuator(WuClass):
        def __init__(self, pin):
            WuClass.__init__(self)
            self.loadClass('Light_Actuator')
            self.light_actuator_gpio = pin_mode(pin, PIN_TYPE_DIGITAL, PIN_MODE_OUTPUT)

        def update(self,obj,pID=None,val=None):
            try:
                if pID == 0:
                    if val == True:
                        digital_write(self.light_actuator_gpio, 1)
                        print "Light Actuator On"
                    else:
                        digital_write(self.light_actuator_gpio, 0)
                        print "Light Actuator Off"
            except IOError:
                print ("Error")

    class MyDevice(Device):
        def __init__(self,addr,localaddr):
            Device.__init__(self,addr,localaddr)

        def init(self):
            cls = Light_Actuator(Light_Actuator_Pin)
            self.addClass(cls,0)
            self.obj_light_actuator = self.addObject(cls.ID)

    if len(sys.argv) <= 2:
        print 'python udpwkpf.py <ip> <port>'
        print '      <ip>: IP of the interface'
        print '      <port>: The unique port number in the interface'
        print ' ex. python <filename> <gateway ip> <local ip>:<any given port number>'
        print ' ex. python udpdevice_grove_kit_sample.py 192.168.4.7 127.0.0.1:3000'
        sys.exit(-1)

    d = MyDevice(sys.argv[1],sys.argv[2])
    reactor.run()