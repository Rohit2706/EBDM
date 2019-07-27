def probability(df, features):
    for feat in features.keys():
        series = df[feat].value_counts(normalize=True,sort=False)
        for cat in series.index:
            features[feat].categories[cat].prob = series[cat]

    return features

def entropy(features):
    for feat in features.values():
        for cat in feat.categories.values():
            if(cat.prob):
                cat.entropy = (-1)*cat.prob*math.log(cat.prob)
            else:
                pass

    return features
