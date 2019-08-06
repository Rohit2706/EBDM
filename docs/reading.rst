Reading Data
============

Make sure that you've separated ordinal and nominal into separate CSV files.

Usage

.. code-block:: python

	nominal_features_dict = ebd.read_nom('nominal_data.csv')
	ordinal_features_dict = ebd.read_ord('ordinal_data.csv')
	
Nominal Data
------------
.. automodule:: nominal_data
	:members:

Ordinal Data
------------
.. automodule:: ordinal_data
	:members: