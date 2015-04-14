// Collection definitions of general devices
var DeviceCollection = CollectionWS.extend({
  url: 'devices',
  model: DeviceModel,
  initialize: function(){
  },

  sortModelsByAttr: function(attr){
    modelObjs= []
    for(var i = 0; i < this.models.length; i++){
      model = this.models[i]
      modelObj = {}
      modelObj['model'] = model
      modelObj[attr] = model.getAttr(attr)
      modelObjs.push(modelObj)
    }

    modelObjs.sort(function(a,b){
      return a[attr] - b[attr]
    })

    return modelObjs.map(function(obj){return obj.model})
  },

  getDevices: function(){
    return this.models
  },

  getByAttr: function(attr, attrValue){
    for ( var i = 0; i < this.models.length; i++){
      var model = this.models[i];
      var modelAttrValue = model.getAttr(attr);
      if(modelAttrValue == attrValue)
        return model;
    }
  },

  getDeviceTypes: function(){
    devices = this.getDevices()
    typesObj = {}
    for(var i = 0; i < devices.length; i++){
      device = devices[i]
      typeID = device.getTypeID()
      if (!typesObj.hasOwnProperty(typeID)){
        typesObj[typeID] = this.deviceDict[typeID]
      }
    }
    typesArray = $.map(typesObj, function(value, index) { return [value]; });
    return typesArray
  }

})

//Different groupings of 
var ValueCollection = NestedCollection.extend({
  model: ValueModel,
  initialize: function(){
  },

  sortModelsByAttr: function(sortObj){

    var attr = sortObj.attr;
    var ascDesc = sortObj.ascDesc;
    var models = sortObj.models;

    if( models == undefined )
      models = this.models;

    var valueObjs = [];
    for(var i = 0; i < models.length; i++){
      value = models[i];
      valueObj = {};
      valueObj['model'] = value;
      valueObj[attr] = value.getAttr(attr);
      valueObjs.push(valueObj);
    }

    valueObjs.sort(function(a,b){
      if(ascDesc == 1){
        return a[attr] - b[attr];
      }
      else
        return b[attr] - a[attr];
    })

    return valueObjs.map(function(obj){return obj.model});
  },

  getShownValues: function(){
    var shownValues = [];

    for(var i = 0; i < this.models.length; i++){
      var model = this.models[i]
      if( !model.getAttr('hidden') ){
        shownValues.push(model)
      }
    }

    return shownValues;
  },

  getDisplayValues: function(){
    var shownValues = this.getShownValues();
    var displayValues = [];

    for(var i = 0; i < shownValues.length; i++){
      var shownValue = shownValues[i]
      
      if( shownValue.getAttr('display') > 0 ){
        displayValues.push(shownValue)
      }
    }
    var sortedDisplay = this.sortModelsByAttr({
      attr: 'display',
      ascDesc: 1,
      models: displayValues
    })

    return sortedDisplay;
  },

  getInfoList: function(){
    var values = this.models
    var infoArray = []
    for( var i = 0; i < values.length; i++){
      var value = values[i]
      infoArray.push(value)
    }
    return infoArray
  },

  getByAttr: function(attr, attrValue){
    for ( var i = 0; i < this.models.length; i++){
      var model = this.models[i];
      var modelAttrValue = model.getAttr(attr);
      if(modelAttrValue == attrValue)
        return model;
    }
  },
})

var AttrCollection = CollectionWS.extend({
  url:'attrs',
  model: AttrModel,
  initialize: function(data){
  },

  getByKey: function(attrKey){
    var attrs = this.models;
    for( var i = 0; i < attrs.length; i++){
      var attr = attrs[i];
      if (attr.get('key') == attrKey)
        return attr;
    }
  },

  getValue: function(id){
    model = this.get(id)
    return model.getValue()
  },

  getInfoList: function(){
    var attrs = this.models
    var infoArray = []
    for( var i = 0; i < attrs.length; i++){
      var attr = attrs[i]
      var attrID = attr.get('id')
      if( attrID[0] == '_' ){
        //hidden attribute so we don't care about it
      }else{
        infoArray.push(attr)
      }
    }
    return infoArray
  },

  jsonIt: function(){
    attrs = {}
    modelsJson = this.toJSON()
    for(var i= 0; i < modelsJson.length; i ++){
      modelJson = modelsJson[i]
      key = modelJson.id
      value = modelJson.value
      attrs[key] = value
    }
    return attrs
  },
})