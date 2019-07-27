def probability(df, features):
    for feat in features.keys():
        series = df[feat].value_counts(normalize=True,sort=False)
        for cat in series.index:
            features[feat].categories[cat].prob = series[cat]

    return features
