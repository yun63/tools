--
-- TplResearchData
-- auto generate by tools
-- Copyright(R) GOW
--

TplResearchData = {};

TplResearchData.data = {

};



function TplResearchData.len(self)
	return 0
end

function TplResearchData.get(self, id, level)
	return self.data[id .. '_' .. level]
end

