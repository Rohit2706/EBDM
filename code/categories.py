class Categories:
    """
    A class used to represent a category of a feature. A category represents a 
    choice given in a question.

    ...

    Attributes
    ----------
    name : str
        the name of the category
    index : int
        the index is used to identify the categories. It preserves the order of the 
        categories in case of ordinal features.
    prob : float
        the occurence probability of a category of a feature in a particular population
    entropy : int
        the entropy of a category of a feature in a particular population given by
        entropy = -p * log(p) where p is the occurence probability
        
    """
  
    def __init__(self, name, index):
        """
        Parameters
        ----------
        name : str
            the name of the category
        index : int
            the index is used to identify the categories. It preserves the order of the 
            categories in case of ordinal features.
        """

        self.name = name
        self.index = index
        self.prob = 0
        self.entopy = 0
