
require('TplTalent')

local conf  = TplTalent.data;

print("######################")

for k, v in pairs(conf) do
    print(k, v)
end

