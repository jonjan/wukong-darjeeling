import os, sys
import unittest
sys.path.append(os.path.join(os.path.dirname(os.path.abspath(__file__)), '../..'))
from test_environment_device import WuTest
from configuration import *

class TestDiscovery(unittest.TestCase):

    def setUp(self):
    	self.test = WuTest(False, False)

    def test_basic_discoveryAPI(self):
    	self.test.discovery()
        res = self.test.countWuObjectByWuClassID(204)
        self.assertEqual(res, 3)

        res = self.test.countWuObjectByWuClassID(10)
        self.assertEqual(res, 3)

        res = self.test.countWuObjectByWuClassID(15)
        self.assertEqual(res, 3)


if __name__ == '__main__':
    unittest.main()