#! /usr/bin/env python
# -*- coding: utf-8 -*-

import rospy

from std_msgs.msg import Int32

rospy.init_node('topic_publisher') 
#ノードの名前 => 基本的に1プログラム1つ

pub = rospy.Publisher('counter', Int32, queue_size=10)
#トピック名, 型名, バッファサイズ的なもの

rate = rospy.Rate(1)
count = 0
while not rospy.is_shutdown():
    print(count)
    pub.publish(count)
    count += 1
    rate.sleep()
