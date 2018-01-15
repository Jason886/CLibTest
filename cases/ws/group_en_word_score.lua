local CaseComm = require 'cases/CaseComm'
return {

	{
		name = "ws_en_word_score",
		copyTimes = 2,
		input = {

		},
		run = CaseComm.Group_Run,
		cases = {
			"cases/ws/case_en_word_score",
			"cases/ws/case_en_word_score2",
		},
	},

}