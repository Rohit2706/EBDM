# !/usr/bin/env python3
# -*- coding: utf-8 -*-

"""
Created on Fri Jun 28 11:34:13 2019

@author: Rohit Jain, Ishita Mediratta, Kartik Bhatia, Anmol Agarwal, Syed Ahsan Abbas, Nischit Soni

This code is meant to calculate the entropy-based distances using both, 
ordinal & nominal attributes.

Source: Y. Zhang, Y. Cheung and K. C. Tan, "A Unified Entropy-Based 
Distance Metric for Ordinal-and-Nominal-Attribute Data Clustering," in IEEE 
Transactions on Neural Networks and Learning Systems.
doi: 10.1109/TNNLS.2019.2899381
    
    * Data: 
        1. We are given a dataset(as .csv file) that contains 
        the phenotype attribute and the order of the choices that were given 
        on the questionnaire - Separate into 2 datasets - Ordinal & Nominal
        2. CSV of the responses filled
        
"""

''' IMPORTING THE DEPENDENCIES '''

import pandas as pd
import math

from categories import *
from features import *
from feature_functions import *
from nominal_data import *
from ordinal_data import *
from distance import *
