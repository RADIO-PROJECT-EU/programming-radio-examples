#!/usr/bin/env python
import os
import rospy
from std_msgs.msg import Float32
from radio_services.srv import InstructionWithAnswer

sub = None
running = False
pub = None
input_topic = ""

def init():
    global input_topic, sub, pub, running
    rospy.init_node("radio_py_example")
    input_topic = rospy.get_param("~input_topic", "/radio_py_example/input")
    pub = rospy.Publisher("radio_py_example/output", Float32, queue_size=1)
    rospy.Service("/radio_py_example/node_state_service", InstructionWithAnswer, nodeStateCallback)
    if running:
        sub = rospy.Subscriber(input_topic, Float32, squareCallback)
    while not rospy.is_shutdown():
        rospy.spin()

def nodeStateCallback(req):
    global running, sub
    # Stop the node
    if req.command == 0 and running:
        sub.unregister()
        running = False
        print 'Stopped radio_py_example!'
    # Start the node
    elif req.command == 1 and not running:
        sub = rospy.Subscriber(input_topic, Float32, squareCallback)
        running = True
        print 'Started radio_py_example!'
    # Return the current state
    return running

def squareCallback(msg):
    global pub
    res = Float32()
    res.data = msg.data * msg.data

    pub.publish(res)

if __name__ == '__main__':
    init()