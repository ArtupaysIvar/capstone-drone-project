#!/usr/bin/env python3

# import os
import rclpy
from rclpy.node import Node
from rclpy.qos import qos_profile_sensor_data
from sensor_msgs.msg import Image
from cv_bridge import CvBridge

import cv2
import numpy as np
from ultralytics import YOLO

from pixel_msgs.msg import PixelCoordinates
from ament_index_python.packages import get_package_share_directory


class GrabVideo(Node):

    def __init__(self):
        super().__init__('grab_video')
        
        # subscription
        self.subscription1 = self.create_subscription(
            Image, 'camera_drone1', 
            self.drone1_cam_callback, 10)

        self.subscription2 = self.create_subscription(
            Image, 'camera_drone2', 
            self.drone2_cam_callback, 10)

        self.subscription3 = self.create_subscription(
            Image, 'camera_drone3', 
            self.drone3_cam_callback, 10)
        
        # publishers
        self.publisher_1 = self.create_publisher(
            PixelCoordinates, 'pixel_topic1', 10)
        
        self.publisher_2 = self.create_publisher(
            PixelCoordinates, 'pixel_topic2', 10)
        
        self.publisher_3 = self.create_publisher(
            PixelCoordinates, 'pixel_topic3', 10)

        # timer
        self.timer = self.create_timer(0.5, self.timer_callback)

    def drone1_cam_callback(self, data_cam1):    
        # Convert ROS Image message to OpenCV image
        current_frame = self.br.imgmsg_to_cv2(data_cam1, desired_encoding="bgr8")
        image = current_frame
        # Object Detection
        results = model.predict(image, classes=[0, 2])
        img = results[0].plot()
        # Show Results
        cv2.imshow('Detected Frame', img)    
        cv2.waitKey(1)

    def drone2_cam_callback(self, data_cam2):
        # Convert ROS Image message to OpenCV image
        current_frame = self.br.imgmsg_to_cv2(data_cam2, desired_encoding="bgr8")
        image = current_frame
        # Object Detection
        results = model.predict(image, classes=[0, 2])
        img = results[0].plot()
        # Show Results
        cv2.imshow('Detected Frame', img)    
        cv2.waitKey(1)

    def drone3_cam_callback(self, data_cam3):
        # Display the message on the console
        self.get_logger().info('Receiving video frame')
    
        # Convert ROS Image message to OpenCV image
        current_frame = self.br.imgmsg_to_cv2(data_cam3, desired_encoding="bgr8")
        image = current_frame
        # Object Detection
        results = model.predict(image, classes=[0, 2])
        img = results[0].plot()
        # Show Results
        cv2.imshow('Detected Frame', img)    
        cv2.waitKey(1)
    def timer_callback():
        msg = PixelCoordinates()

        self.publisher1.publish(msg1)
        self.publisher2.publish(msg2)
        self.publisher3.publish(msg3)
        
def main(args=None):
    rclpy.init(args=args)
    node = GrabVideo()
    rclpy.spin(node)
    node.destroy_node()
    rclpy.shutdown()


if __name__ == '__main__':
    main()
