--
-- sys_test
-- auto generate by tools
-- Copyright(R) GOW
--

sys_test = {}

sys_test.data = {
	["1"] = {
		lvl = 1,
		exp = 100
	},
	["2"] = {
		lvl = 2,
		exp = 200
	},
	["3"] = {
		lvl = 3,
		exp = 300
	},
	["4"] = {
		lvl = 4,
		exp = 400
	},
	["5"] = {
		lvl = 5,
		exp = 500
	},
	["6"] = {
		lvl = 6,
		exp = 600
	},
	["7"] = {
		lvl = 7,
		exp = 700
	},
	["8"] = {
		lvl = 8,
		exp = 800
	},
	["9"] = {
		lvl = 9,
		exp = 900
	},
	["10"] = {
		lvl = 10,
		exp = 1000
	}
};



function sys_test.get(self, lvl)
	return self.data[tostring(lvl)]
end

