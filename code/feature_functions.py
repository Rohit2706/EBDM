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


def std_entropy(features):
    for feat in features.values():
        if(feat.num_cat):
            feat.std_entropy = math.log(feat.num_cat)
        else:
            pass

    return features

def feature_entropy(features):
    for feat in features.values():
        feat_entropy = 0
        for cat in feat.categories.values():
            feat_entropy = feat_entropy + cat.entropy

        feat.entropy = feat_entropy

    return features

def reliability(features):
    for feat in features.values():
        try:
            feat.reliability = feat.entropy/ feat.std_entropy
        except ZeroDivisionError as error:
            Logging.log_exception(error)

    return features

def total_reliability(features):
    total_rel = 0
    for feat in features.values():
        total_rel = total_rel + feat.reliability

    return total_rel

def weights(features, total_reliability):
    for feat in features.values():
        feat.weights = feat.reliability/ total_reliability

    return features
