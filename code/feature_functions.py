def probability(df, features):
    """
    Calculates the occurence probability of all the categories for every feature.
    
    Parameters
    ----------
    df : panda dataframe
        The dataset of the population in the format:
                 | Feedback  |  Color  |   Hooby   .........
        ----------------------------------------------------
        Person A |   Poor    |   Red   |  Football
                 '           '           '
                 '           '           '
    features : dictionary
        a dictionary of features with keys as feature name and values as objects of
        feature class.
        
    Returns
    -------
    features : dictionary
        a dictionary of features with keys as feature name and values as objects of
        feature class with updated probability values.
    """
    
    for feat in features.keys():
        series = df[feat].value_counts(normalize=True,sort=False)
        for cat in series.index:
            features[feat].categories[cat].prob = series[cat]

    return features

def entropy(features):
    """
    Calculates the entropy of all the categories for every feature.
    
    Parameters
    ----------
    features : dictionary
        a dictionary of features with keys as feature name and values as objects of
        feature class.
     
    Returns
    -------
    features : dictionary
        a dictionary of features with keys as feature name and values as objects of
        feature class with updated entropy values.
    """
    
    for feat in features.values():
        for cat in feat.categories.values():
            if(cat.prob):
                cat.entropy = (-1)*cat.prob*math.log(cat.prob)
            else:
                pass

    return features


def std_entropy(features):
    """
    Calculates the standard entropy of all the features.
    
    Parameters
    ----------
    features : dictionary
        a dictionary of features with keys as feature name and values as objects of
        feature class.
     
    Returns
    -------
    features : dictionary
        a dictionary of features with keys as feature name and values as objects of
        feature class with updated standard entropy values.
    """
    
    for feat in features.values():
        if(feat.num_cat):
            feat.std_entropy = math.log(feat.num_cat)
        else:
            pass

    return features

def feature_entropy(features):
    """
    Calculates the entropy of all the features.
    
    Parameters
    ----------
    features : dictionary
        a dictionary of features with keys as feature name and values as objects of
        feature class.
     
    Returns
    -------
    features : dictionary
        a dictionary of features with keys as feature name and values as objects of
        feature class with updated feature entropy values.
    """
    
    for feat in features.values():
        feat_entropy = 0
        for cat in feat.categories.values():
            feat_entropy = feat_entropy + cat.entropy

        feat.entropy = feat_entropy

    return features

def reliability(features):
    """
    Calculates the reliability of all the features.
    
    Parameters
    ----------
    features : dictionary
        a dictionary of features with keys as feature name and values as objects of
        feature class.
     
    Returns
    -------
    features : dictionary
        a dictionary of features with keys as feature name and values as objects of
        feature class with updated reliability values.
    """
    
    for feat in features.values():
        try:
            feat.reliability = feat.entropy/ feat.std_entropy
        except ZeroDivisionError as error:
            Logging.log_exception(error)

    return features

def total_reliability(features):
    """
    Calculates the total reliability of the features.
    
    Parameters
    ----------
    features : dictionary
        a dictionary of features with keys as feature name and values as objects of
        feature class.
     
    Returns
    -------
    total_rel : float
        the total reliability of the features
    """
    
    total_rel = 0
    for feat in features.values():
        total_rel = total_rel + feat.reliability

    return total_rel

def weights(features, total_reliability):
    """
    Calculates the weights of all the features.
    
    Parameters
    ----------
    features : dictionary
        a dictionary of features with keys as feature name and values as objects of
        feature class.
    total_reliability : float
        the total reliability of the features
        
    Returns
    -------
    features : dictionary
        a dictionary of features with keys as feature name and values as objects of
        feature class with updated weight values.
    """
    
    for feat in features:
        features[feat].weight = features[feat].reliability/ total_reliability

    return features
