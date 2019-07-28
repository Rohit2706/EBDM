class Features:
    def __init__(self, _name, _feat_type):
        self.name = _name
        self.feat_type = _feat_type
        self.num_cat = 0
        self.categories = dict()
        self.entropy = 0
        self.std_entropy = 0
        self.reliability = 0
        self.weight = 0
        self.distance = dict()
        self.category_order = dict()
