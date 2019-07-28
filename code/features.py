class Features:
    """
    A class used to represent a feature. A feature represennts question asked in the
    questionnaire.
    ...
    Attributes
    ----------
    name : str
        the name of the feature
    feat_type : str
        the type of feature: ordinal or nominal
    num_cat : int
        the number of categories for a feature in the questionnaire
    categories : dictionary
        a dictionary with keys as category name and values as objects of Categories class
    entropy : float
        the entropy of a feature in a particular population, given by
        entropy of feature = sum(entropy of categories)
    std_entropy : float
        the standard entropy of a feature given by log(num_cat)
    reliability : float
        the reliability of a feature given by entropy/ std_entropy
    weight : float
        the weight of a feature given by reliability/ total_reliability
        
    """
    
    def __init__(self, name, feat_type):
        self.name = name
        self.feat_type = feat_type
        self.num_cat = 0
        self.categories = dict()
        self.entropy = 0
        self.std_entropy = 0
        self.reliability = 0
        self.weight = 0
        self.distance = dict()
        self.category_order = dict()
