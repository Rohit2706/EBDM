def read_ord(data):
    """
    Reads the ordinal data from the data file and instantiate the Features and
    Categories classes.

    Parameters
    ----------
    data : str
        The file location of the spreadsheet containing ordibnal categories in the format:
        Feature  | Category1 | Category2 | Category3.........
        ----------------------------------------------------
        Feedback |   Poor    |    Good   |  Excellent
                 '           '           '
                 '           '           '
                 
    Returns
    -------
    features : dictionary
        a dictionary of features with keys as feature name and values as objects of
        feature class.
    """
    
    try:
        ordinal_categories = pd.read_csv(data,header=None,index_col=0)
    except ImportError:
        print('Error Importing Ordinal Data')

    features = dict()
    
    for feat in ordinal_categories.index:
        feat_instance = Features(feat,'ordinal')
        
        cat_names = ordinal_categories.loc[feat,ordinal_categories.loc[feat,:].notnull()].tolist()
        feat_instance.num_cat = len(cat_names)
        
        for _index, _name in enumerate(cat_names):
            feat_instance.categories[_name] = Categories(_name, _index)
            feat_instance.category_order[_index] = _name
           
        features[feat] = feat_instance
        
    return features
