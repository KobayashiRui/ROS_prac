#! /usr/bin/env python
# -*- coding: utf-8 -*-

import rospy

from std_msgs.msg import Int32MultiArray

rospy.init_node('topic_publisher') 
#ノードの名前 => 基本的に1プログラム1つ

pub = rospy.Publisher('counter', Int32MultiArray, queue_size=100)
#トピック名, 型名, バッファサイズ的なもの

rate = rospy.Rate(1)
data = [0,0,0,0]
count = Int32MultiArray(data=data)

while not rospy.is_shutdown():
    print(count.data)
    pub.publish(count)
    count.data = map(lambda x: x+1, count.data)
    rate.sleep()
