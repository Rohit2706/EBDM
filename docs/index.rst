.. EBDM documentation master file, created by
   sphinx-quickstart on Sat Aug  3 23:16:37 2019.
   You can adapt this file completely to your liking, but it should at least
   contain the root `toctree` directive.

Welcome to EBDM's documentation!
================================

Requirements
------------
Before getting started, make sure that you have the following libraries already installed

.. code-block:: python

	import pandas as pd
	import math

.. note::
	EBDM requires Python 3.x

Quick Install
-------------

Download the package using pip

.. code-block:: shell

	pip install EBDM

In your source file, import the library and start using the functions step-by-step as mentioned in the below section

.. code-block:: python
	
	import EBDM as ebd

For accessing modules, use 

.. code-block:: python

   ebd.<module_name>

API Contents
------------

.. toctree::
   :maxdepth: 2

   reading
   features
   categories
   distance


Indices and tables
==================

* :ref:`genindex`
* :ref:`modindex`
* :ref:`search`
