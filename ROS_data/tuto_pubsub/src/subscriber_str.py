#! /usr/bin/env python
#-*- coding: utf-8 -*-

import rospy

from std_msgs.msg import String

def callback(msg):
    print(msg.data)

rospy.init_node('topic_subscriber')
#ノード名

sub = rospy.Subscriber('counter', String, callback)
#購読(接続)するトピック名, 型名, 起動する関数名
rospy.spin()
