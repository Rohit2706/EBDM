def read_nom(data):
    try:
        nominal_categories = pd.read_csv(data,header=None,index_col=0)
    except ImportError:
        print('Error Importing Nominal Data')

    features = dict()
    
    for feat in nominal_categories.index:
        feat_instance = Features(feat,'nominal')
        
        cat_names = nominal_categories.loc[feat,nominal_categories.loc[feat,:].notnull()].tolist()
        feat_instance.num_cat = len(cat_names)
        
        for _index, _name in enumerate(cat_names):
            feat_instance.categories[_name] = Categories(_name, _index)
            feat_instance.category_order[_index] = _name
           
        features[feat] = feat_instance
        
    return features
