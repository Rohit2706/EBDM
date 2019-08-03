def distance_between_categories(features):
    """
    Calculates the distance between all the categories for every feature.
    
    Parameters
    ----------
    features : dictionary
        a dictionary of features with keys as feature name and values as objects of
        feature class
     
    Returns
    -------
    features : dictionary
        a dictionary of features with keys as feature name and values as objects of
        feature class with updated distance values
    """
    
    for feat in features:
        for i in features[feat].category_order.keys():
            features[feat].distances[features[feat].category_order[i]] = dict()

    for feat in features:
        for i in features[feat].category_order.keys():
            features[feat].distances[features[feat].category_order[i]][features[feat].category_order[i]] = 0               
            
            if (features[feat].feat_type == 'ordinal'):
                for j in range(i+1, features[feat].num_cat):
                    prev = features[feat].distances[features[feat].category_order[i]][features[feat].category_order[j-1]]
                    curr = prev + (features[feat].weight)*(features[feat].categories[features[feat].category_order[j]].entropy)
                    
                    features[feat].distances[features[feat].category_order[i]][features[feat].category_order[j]] = curr
                    features[feat].distances[features[feat].category_order[j]][features[feat].category_order[i]] = curr
            else:
                for j in range(i+1, features[feat].num_cat):
                    curr = (features[feat].weight)*(features[feat].categories[features[feat].category_order[j]].entropy + features[feat].categories[features[feat].category_order[i]].entropy) 
                    
                    features[feat].distances[features[feat].category_order[i]][features[feat].category_order[j]] = curr 
                    features[feat].distances[features[feat].category_order[j]][features[feat].category_order[i]] = curr
                    
    return features
    

def distance_between_individuals(data, features):
    """
    Calculates the distance between individuals of a population
    
    Parameters
    ----------
    df : panda dataframe
        the dataset of the population in the format:
                 | Feedback  |  Color  |   Hobby  
        ------------------------------------------
        Person A |   Poor    |   Red   |  Football
                
    features : dictionary
        a dictionary of features with keys as feature name and values as objects of
        feature class.
     
    Returns
    -------
    dist_mat : list
        a list of lists representing the pairwise distance matrix of the individuals
    """
    
    dist_mat = []
    
    for index1 in data.index:
        
        dist_temp = []
        for index2 in data.index: 
            
            dist = 0
            for col in data.columns:     
                
                if (type(data.loc[index1,col]) == str and type(data.loc[index2,col]) == str):
                    dist += (features[col].distances[data.loc[index1,col]][data.loc[index2,col]])**2
            
            dist_temp.append(math.sqrt(dist))
        
        dist_mat.append(dist_temp)
            
    dist_mat = pd.DataFrame(dist_mat)    
    
    return dist_mat
