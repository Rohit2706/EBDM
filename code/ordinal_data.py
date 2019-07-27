def read_ord(_data, _header, _index ):
    try:
        if(_index):
            ordinal_categories = pd.read_csv(_data,header=_header,index_col=0)
        else:
            ordinal_categories = pd.read_csv(_data,header=_header,index_col=0)
    except ImportError:
        print('Error Importing Ordinal Data')

    #Assign the instances as we discussed earlier.
