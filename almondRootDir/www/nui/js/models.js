// Models
var DeviceModel = ModelWS.extend({
	url:'device',
	initialize: function(data){
		var that = this;

		var attrs = data.attrs;
		this.set({attrs: new AttrCollection(attrs)});
		this.get('attrs').on('change', function(){
	      that.trigger('change')
	    })

		var values = data.values;
		this.set({values: new ValueCollection(values)});
		this.get('values').on('change', function(){
	      	that.trigger('change')
	    })
	},

	getValueByAttr: function(attr, value){
		return this.get('values').getByAttr(attr, value);
	},

	getValue: function(valueID){
		var valueModel = this.get('values').get(valueID)
		return valueModel
	},

	getShownValues: function(valueID){
		var values = this.get('values');
		return values.getShownValues();
	},

	getDisplayValues: function(valueID){
		var values = this.get('values');
		return values.getDisplayValues();
	},

	getStateValue: function(){
		var displayValues = this.getDisplayValues();
		for( var i in displayValues){
			var displayValue = displayValues[i]
		}
		return displayValues[0];
	},

	getState: function(){
		var stateValue = this.getStateValue();
		var states = stateValue.getAttr('states');
		var value = stateValue.getAttr('value');
		var state = states[value];
		if(state)
			return state;
		else
			return states[0]
	},

	getAttr: function(attrKey){
		var attrs = this.get('attrs');

		if( attrKey == undefined)
			return attrs;
		else{			
			var attr = attrs.getByKey(attrKey);
			return attr.get('value')
		}
	},

	setAttr: function(setObj){
		var that = this;
		$.each(setObj, function(key, value){
	        var attrs = that.get('attrs');
	        var attrModel = attrs.get(key);

	        attrModel.set({
	          value: value
	        });
	    });
	},

	toggle: function(){
		var stateValue = this.getStateValue();
		var type = stateValue.getAttr('type');
		switch (type){
			case 'switch':
				stateValue.toggle();
				break;
			default:
				console.log('Can\'t toggle a', type);
		}
	},

	getColor: function(){
		var stateValue = this.getStateValue();
		return this.valueColor(stateValue.getAttr('value'), 1)
	},

	valueColor: function(currentStatus, opacity){
		var colorCount = Object.keys(window.Colors).length;
		// var colorIndex = Math.floor(Math.random() * colorCount)
		var colorIndex = parseInt(this.getAttr('typeId')) % colorCount;

		var rgb = $.extend({}, window.Colors[colorIndex])
		
		if(!currentStatus){
	// If the the current status is not on
	// then dim the color
			var dimmingMultiplier = 0.3
			rgb.r = rgb.r * dimmingMultiplier
			rgb.g = rgb.g * dimmingMultiplier
			rgb.b = rgb.b * dimmingMultiplier
		}
		var string = rgbaToString( rgb.r, rgb.g, rgb.b, opacity)
		return string
	},

	getInfoList: function(){
		var attrs = this.get('attrs').getInfoList()
		var values = this.get('values').getInfoList()
		var infoList = attrs.concat(values)
		return infoList
	}
})

var ValueModel = NestedModel.extend({
	initialize: function(data){
		var that = this;

		var attrs = data.attrs;	
		this.set({attrs: new AttrCollection(attrs)})
		this.get('attrs').on('change', function(){
	      	that.trigger('change')
	    })
	},

	textValue: function(){
		var value = this.getAttr('value');
		var valueType = this.getAttr('type');
		switch( valueType ){
			case 'number':
				return {
					main: Math.round(value),
					sub: this.getAttr('unit')
				}
			case 'state':
				var states = this.getAttr('states');
				return{
					main: states[value].text
				}
			case 'alert':
				var state = this.getState();
				return {
					top: "ALERT!",
					main: "\\('o')/"
				}

			case 'undefined':
			default:
				return {
					top: "Unsupported Device",
					main: "( T_T)"
				}
		}

	},

	getAttr: function(attrKey){
		var attrs = this.get('attrs');
		var attr = attrs.getByKey(attrKey);
		if( attr != undefined ){
			return attr.get('value');
		}else {
			return undefined
		}
	},

	getInfo: function(){
		var valueInfo = this.get('attrs').jsonIt();
		var value = this.textValue();
		valueText = value.main 
		
		if(value.sub != undefined)
			valueText = valueText + ' ' + value.sub
		
		return {
			key: valueInfo.name,
			value: valueText,
			editable: 0
		}
	},

	getState: function(value){
		if( value == undefined)
			value = this.getAttr('value');

		var states = this.getAttr('states');

		try {
			var state = states[value]
		}
		catch (e) {
		   console.log(e)
		   var state = states[0]
		}

		return state
	},

	setAttr: function(setObj){
		that = this
		$.each(setObj, function(key, value){
	        var attrs = that.get('attrs')
	        var attrModel = attrs.getByKey(key)
	        attrModel.save({
	          value: value
	        })
	    });
	},

	toggle: function(){
		var currentValue = this.getAttr('value');
		var stateCount =  Object.keys(this.getAttr('states')).length;
		var newValue = (currentValue + 1) % stateCount;
		this.setAttr({
			value: newValue
		})
	}
})

var AttrModel = ModelWS.extend({
	url:'attr',
	initialize: function(data){
	},

	getValue: function(){
		return this.get('value')
	},

	getInfo: function(){
		id = this.get('id')
		value = this.get('value')
		return {
			key: id,
			value: value,
			editable: this.get('whereToSave')
		}
	},
})