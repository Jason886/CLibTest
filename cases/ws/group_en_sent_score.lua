local CaseComm = require 'cases/CaseComm'
return {

        {
                name = "ws_en_sent_score",
                copyTimes = 1,
                input = {

                },
                run = CaseComm.Group_Run,
                cases = {
                        "cases/ws/case_en_sent_score",
                        --"cases/ws/case_en_sent_score2",
                },
        },

}