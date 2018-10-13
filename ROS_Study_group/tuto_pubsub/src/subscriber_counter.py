#! /usr/bin/env python
#-*- coding: utf-8 -*-

import rospy

from std_msgs.msg import Int32

def callback(msg):
    print(msg)
    print(msg.data)

rospy.init_node('topic_subscriber')
#ノード名

sub = rospy.Subscriber('counter', Int32, callback)
#購読(接続)するトピック名, 型名, 起動する関数名
rospy.spin()
