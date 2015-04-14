var DeviceListView = BaseView.extend({
  el: 'div',
  events: {
    // "mousemove  .expandCollapseOverlay": "mouseMove",
    // "mouseout   .expandCollapseOverlay": "mouseOut",
    // "click      .expandCollapseOverlay": "expandCollapse",
    // "click      #listToBoxButton"      : "listToBox",
    // "click      #boxToListButton"      : "boxToList"
  },
  boxToList: function(click){
    this.deviceView = "list"

    var deviceElems = this.$el.find(".item")
    for( var i = 0; i < deviceElems.length; i++){
      var deviceElem = deviceElems[i]
      var deviceContent = $(deviceElem).find('.item-content')
      var classes = deviceContent[0].classList
      deviceContent.addClass('w12')
    }
    
    this.container.packery();

    var deviceElems = this.$el.removeClass('boxView')
    var deviceElems = this.$el.addClass('listView')
  },
  listToBox: function(click){
    this.deviceView = "box"

    var deviceElems = this.$el.find(".item")
    for( var i = 0; i < deviceElems.length; i++){
      var deviceElem = deviceElems[i]
      var deviceContent = $(deviceElem).find('.item-content')
      deviceContent.removeClass('w12')
    }

    this.container.packery();

    var deviceElems = this.$el.removeClass('listView')
    var deviceElems = this.$el.addClass('boxView')
  },
  getMouseXY: function(event){
    var mouseX, mouseY

    if(event.offsetX == undefined){
      mouseX = event.originalEvent.layerX
      mouseY = event.originalEvent.layerY
    }else{
      mouseX = event.offsetX
      mouseY = event.offsetY
    }

    return [mouseX, mouseY]
  },
  expandCollapse: function(event){
    var mouseXY = this.getMouseXY(event)
    var mouseX = mouseXY[0]
    var mouseY = mouseXY[1]

    var elem = $(event.target).closest('.item');
    var elemContent = elem.find('.item-content');
    var elemContent = elem.find('.item-content');


    var horizontalVertical = this.horizontalVertical(elem, mouseX, mouseY)
    var heightWidth = this.heightWidth(elem, mouseX, mouseY)
    var currDimension = elem.attr(heightWidth)
    var nextDimension = this.oppositeDimension(elem, currDimension)

    elem.attr(heightWidth, nextDimension)
    elemContent.switchClass(currDimension,nextDimension,0)
    this.updateArrows(elem, horizontalVertical, currDimension, nextDimension)

    var deviceId = elem.attr('deviceId')
    var device = this.collection.get(deviceId)

    setObj = {}
    setObj['_'+heightWidth] = nextDimension
    device.setAttr(setObj)
    this.collection.save()

    this.container.packery( 'fit', elem[0] );
  },
  mouseMove: function(event){
    var mouseXY = this.getMouseXY(event)
    var mouseX = mouseXY[0]
    var mouseY = mouseXY[1]

    var elem = $(event.target).closest('.item');

    switch( this.horizontalVertical(elem, mouseX, mouseY) ){
      case'horizontal':
      //show horizontal expandCollapse arrow
        elem.find('.expandCollapse.horizontal').addClass('show', {duration:200});
        elem.find('.expandCollapse.vertical').removeClass('show', {duration:200});
        break;
      case'vertical':
      //show vertical expandCollapse arrow
        elem.find('.expandCollapse.horizontal').removeClass('show', {duration:200});
        elem.find('.expandCollapse.vertical').addClass('show', {duration:200});
        break;
    }

  },
  mouseOut: function(event){
    var elem = $(event.currentTarget);
    var deviceId = elem.attr('deviceId')
    elem.find('.expandCollapse').removeClass('show', {duration:200});
  },
  initialize: function(data){
    this.collection = window.Devices;
    this.devices = this.collection.getDevices();
    this.deviceView = "box"


    this.template = window.Luci.loadBackboneTemplate("deviceList");
  },
  route: function(part, remaining) {

    viewsToBeReturned = {}

    for(var i = 0; i < this.devices.length; i++){
      device = this.devices[i]
      deviceItemDivID = '#device'+device.getAttr('id')
      listView = new DeviceView(device)
      viewsToBeReturned[deviceItemDivID] = listView
    }

    return viewsToBeReturned;  
    
  },
  render: function() {    
    var renderedTemplate = this.template({
      devices     : this.devices,
      showArrows  : this.showArrows,
    });
    this.$el.html(renderedTemplate);
    setTimeout($.proxy(this.initBoxes), 1000, this);
  },
  initBoxes: function(self){
    var container = $('#deviceList');
    container.packery({
      columnWidth: 158,
      rowHeight: 158,
      gutter: 10,
      transitionDuration: '0.5s'
    });

    // get item elements, jQuery-ify them
    var $itemElems = $( container.packery('getItemElements') );
    // make item elements draggable
    $itemElems.draggable({ 
      distance: 75
    });
    // bind Draggable events to Packery
    container.packery( 'bindUIDraggableEvents', $itemElems );

    self.container = container

    function updateDeviceIndices(layout, items) {
      var elems = container.packery('getItemElements')
      for(var i = 0; i < elems.length; i++){
        item = elems[i]
        elem = $(item)
        device.id = elem.attr('deviceId')
        device = self.collection.get(device.id)

        device.setAttr({
          _index: i
        })
      }
      self.collection.save()
    }

    // container.packery( 'on', 'layoutComplete', updateUserDevicePreferences, this )
    container.packery( 'on', 'dragItemPositioned', updateDeviceIndices, self )
  },
  updateArrows: function(elem, horizontalVertical, currDimension, nextDimension){
    var wrapper = elem.find('.expandCollapse.' + horizontalVertical)
    var expandArrow = wrapper.find('.expand')
    var collapseArrow = wrapper.find('.collapse')
    if( currDimension < nextDimension){
  // collapse
      expandArrow.removeClass('show', {duration:200});
      collapseArrow.addClass('show', {duration:200});
    }else{
  // expand
      expandArrow.addClass('show', {duration:200});
      collapseArrow.removeClass('show', {duration:200});
    }
  },
  heightWidth: function(elem, mouseX, mouseY){
    switch( this.horizontalVertical(elem, mouseX, mouseY) ){
      case 'vertical':
        return 'height'
      case 'horizontal':
        return 'width'
    }
  },
  horizontalVertical: function(elem, mouseX, mouseY){
    var deviceId = elem.attr('deviceId')
    var device = this.collection.get(deviceId)
    if(this.dimensionExpanded(device,'height') || this.deviceView=='list' || this.dimensionExpanded(device,'width') && mouseX < mouseY){
        return 'vertical'
    }else{
        return 'horizontal'
    }
  },
  oppositeDimension: function(elem, nowDimension){
    var id = elem.attr('deviceId')
    var device = this.collection.get(id)
    var widthHeight = nowDimension[0]
    switch( widthHeight ){
      case 'w':
        if (nowDimension == 'w2')
          return device.getAttr('_maxWidth')
        else
          return 'w2'
      case 'h':
        if (nowDimension == 'h2')
          return device.getAttr('_maxHeight')
        else
          return 'h2'
    }
  },
  dimensionExpanded: function(device, dimension){
    var dimension = device.getAttr('_' + dimension)
    if( dimension[1] == '2' )
      return false
    else
      return true
  },
  showArrows: function(device){
    // var doWeShowIt = function(device, dimension){
    //   var dimension = device.getAttr('_' + dimension)
    //   if( dimension[1] == '2' ){
    //     return {
    //       expand    :'show',
    //       collapse  :''
    //     }
    //   }else{
    //     return {
    //       expand    :'',
    //       collapse  :'show'
    //     }
    //   }
    // }
    // return {
    //   horizontal  :doWeShowIt(device,'width'),
    //   vertical    :doWeShowIt(device,'height')
    // }
    return {
      horizontal: {
        expand: 'show',
        collapse: ''
      },
      vertical: {
        expand: 'show',
        collapse: ''
      }
    }
  }
});

var DeviceView = BaseView.extend({
  el: 'div',
  events: {
  },
  initialize: function(device){
    this.template = window.Luci.loadBackboneTemplate("device");
    this.model = device;
  },
  route: function(part, remaining) {
    
    var viewsToBeReturned = {};
    viewsToBeReturned['#device'+this.model.id+'icon'] = new DeviceIconView(this.model);
    // viewsToBeReturned['#device'+this.model.id+'info'] = new DeviceInfoView(this.model);
    
    // var displayValueIndices = this.model.getAttr('_displayValues')

    // for(var i = 0; i < displayValueIndices.length; i++){
    //   var displayValueIndex = displayValueIndices[i];
    //   var valueModel = this.model.getValue(displayValueIndex);

    //   var valueType = valueModel.getAttr('_type');
    //   switch( valueType ){
    //     case 'switch':
    //       var valueView = new SwitchDisplayView(this.model, valueModel);
    //       break;
    //     case 'number':
    //     case 'bool':
    //       var valueView = new NumberDisplayView(this.model, valueModel);
    //   }
      
    //   var valueItemDivID = '#device'+this.model.id+'value'+displayValueIndex;
    //   viewsToBeReturned[valueItemDivID] = valueView;
    // }

    return viewsToBeReturned;   
  },
  render: function() {
    var renderedTemplate = this.template({
      device : this.model,
      attrs  : this.model.get('attrs'),
      values : this.model.get('values')
    });
    this.$el.html(renderedTemplate);
  }
});