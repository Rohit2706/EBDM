Finding Features
================

Example
-------
.. code-block:: python

	# features_dict is the dictionary obtained after reading nominal and/or ordinal data

	from EBDM import feature_functions
	
	feat_std_entropy = std_entropy(features_dict)
	feat_entropy = feature_entropy(feat_std_entropy)
	feat_rel = reliability(feat_entropy)
	total_rel = total_reliability(feat_rel)
	features_dict_weighted = weights(feat_rel, total_rel)

	for f in features_dict.keys():
	    print('name:',f)
	    print('type:',features_dict[f].feat_type)
	    print('num_cat:',features_dict[f].num_cat)
	    print()
	    for cat in features_dict[f].categories.keys():
	        print('    index:',features_dict[f].categories[cat].index)
	        print('    name:',features_dict[f].categories[cat].name)
	        print()
	    print()


Output will be 

.. code-block:: text

	name: You often feel that your life is aimless, with no definite purpose
	type: ordinal
	num_cat: 5
	entropy: 1.4702489763160878
	std_entropy: 1.6094379124341003
	reliability: 0.9135170514856927

	    index: 0
	    name: Strong Disagree
	    prob: 0.13008130081300814
	    entropy: 0.26531325309042425

	    index: 1
	    name: Disagree
	    prob: 0.3902439024390244
	    entropy: 0.3672130124739616

	    index: 2
	    name: Neither
	    prob: 0.21951219512195122
	    entropy: 0.33285676595884867

	    index: 3
	    name: Agree
	    prob: 0.18699186991869918
	    entropy: 0.3135274244487411

	    index: 4
	    name: Strong Agree
	    prob: 0.07317073170731707
	    entropy: 0.19133852034411206

Features Class
--------------

.. automodule:: features
	:members:

Calculating Occurence Probability
---------------------------------

.. automodule:: feature_functions
	:members: probability

Calculating Entropies
---------------------

.. automodule:: feature_functions
	:members: entropy, std_entropy, feature_entropy

Calculating Reliability
-----------------------

.. automodule:: feature_functions
	:members: reliability, total_reliability

Calculating Weights
-------------------

.. automodule:: feature_functions
	:members: weights
