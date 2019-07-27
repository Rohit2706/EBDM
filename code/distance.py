# for each individual
def distance_matrix(df, features):
    dist_outer = list()
    for index1 in df.index:
        dist_inner = list()
        for index2 in df.index:
            if(index1 == index2):
                distance.append(0)
            else:
                for feat in df.columns:
                    dist_val = 0
                    cat1 = features[feat].categories[df.loc[index1, feat]]
                    cat2 = features[feat].categories[df.loc[index2, feat]]
                    if(features[f].feat_type == 'nominal'):
                        dist_val = features[feat].weights * (cat1.entropy + ca2.entropy)
                    else:
                        dist_val

# for each category

def distance(features):
    for feat in features:
        for cat1 in features[feat].categories.values():
            dist_inner = dict()
            for cat2 in features[feat].categories.values():
                if(cat1 == cat2):
                    dist_inner[cat2] = 0
    
