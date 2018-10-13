#! /usr/bin/env python
# -*- coding: utf-8 -*-

import rospy

from std_msgs.msg import String

rospy.init_node('topic_publisher') 
#ノードの名前 => 基本的に1プログラム1つ

pub = rospy.Publisher('counter', String, queue_size=100)
#トピック名, 型名, バッファサイズ的なもの

rate = rospy.Rate(1)
str_data = "Hello World"
while not rospy.is_shutdown():
    print(str_data)
    pub.publish(str_data)
    rate.sleep()
