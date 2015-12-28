

function sys_exp.get(self, id, lvl, color)
	return self[id .. '_' .. lvl .. '_' .. color];
end
