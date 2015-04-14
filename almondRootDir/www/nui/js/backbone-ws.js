/*
 * WebSocket extensions for Backbone.Model and Backbone.Collection
 *
 * The calls to CollectionWS.fetch() will open a socket.io connection to the
 * namespace specified in the collection definition url {url: "/foo"}. This
 * socket listens for updates 
 *
 * Updates made to client-side models can be pushed to the server via the
 * namespace socket as well. Only "update" is supported. These updates contain 
 * a transaction ID. An event with the transaction ID name will be triggered
 * with the result of the update operation {success: true/false}.
 */

var port = 1337;

function S4() {
  return (((1+Math.random())*0x10000)|0).toString(16).substring(1);
}

function uid() {
  return (S4()+S4()+S4());
}

var CollectionWS = NestedCollection.extend({

  save:function(collectionData){
    var socket = this.getSocket();
    var tid = uid();
    socket.emit("save", {tid: tid, url: this.url,  data: this.toJSON()});
  },

  sync: function(method, collection, options) {
    var socket = collection.getSocket(collection, options);
    switch (method) {
      case "read":
        // Return an array  of models for this collection
        var tid = uid();
        socket.on("fetch", function(response) {
          // console.log(tid, response);
          console.log(response.data)
          if (response.success) {
            options.success(collection, response.data, options);
          } 
        });
        socket.emit("fetch", {tid: tid});
        break;
      default:
        console.error("Invalid sync call on collection", collection, method);
    }
  },

  getSocket: function(collection, options) {
    console.log(this.url)
    if (!this._socketio) {
      this._socketio = io(':'+port+'/'+this.url,{
        reconnection: true
      })
      var obj = this;
      this._socketio.on("update", function(response) {
        // data contains an array of model objects to be updated
        console.log('arrived')
        obj.update(response);
      });
      this._socketio.on("connect_error", function(response) {
        // failure to reach backend
        collection.wsFail = true;
        console.log(collection)
        options.failure(collection, response.data, options);
      });
    }
    return this._socketio;
  },
});

var ModelWS = NestedModel.extend({
  
  sync: function(method, model, options) {
    var socket = model.getSocket();
    console.log(model.url)
    console.log(socket)
    switch (method) {
      case "update":
        // send local changes to the server
        var tid = uid();
        socket.on("save", function(response) {
          // console.log(tid, response);
          if (response.success) {
            console.log('save success!')
            // options.success(collection, response.data, options);
          }
        });
        socket.emit("save", {tid: tid, url: model.url, data: model.toJSON()});
        break;
      default:
        console.error("Invalid sync call on model", model, method);
    }
  },

  getSocket: function() {
    if (this.collection) {
      return this.collection.getSocket();
    }
    if (!this._socketio) {
      this._socketio = io.connect(this.urlRoot);
      this._socketio.on("update", function(data) {
        // data contains the model object
        this.set(data);
      });
    }
  },
});


