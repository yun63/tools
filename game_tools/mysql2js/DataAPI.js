
var talent = require('./data/tpl_talent.json');

var Data = function(data) {
  this.data = data;
}

Data.prototype.get = function() {
  var args = Array.prototype.slice.call(arguments);
  var key = args.join('_');
  return this.data[key];
}

module.exports = {
  talent: new Data(talent)
}
