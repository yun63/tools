
var fs = require('fs');

var parser = require('../lib/parser');

console.log(parser.makeHeader('tpl_hero.lua'));

var contents = parser.makeFunc('TplHero', ['id', 'lvl', 'color']);

fs.writeFile('TplHero.lua', contents, function(err) {
  if (err) {
    return console.error(err);
  }
  console.log('^_^ Congratulations! Generate %s.lua successfully!', 'TplHero.lua');
});

var str = '[{"id":1,"lvl":2},{"id":2,"lvl":3}]';

for (var i = 0; i < str.length; i++) {
  console.log(str.charAt(i));
}
