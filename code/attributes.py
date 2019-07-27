class Attributes:
    name = None
    att_type = None
    num_cat = 0

    categories = dict()
    entropy = 0
    std_entropy = 0
    reliability = 0
    weight = 0

    def __init__(self, _name, _attr_type):
        self.name = _name
        self.attr_type = _attr_type

    # introduce functions when required.
