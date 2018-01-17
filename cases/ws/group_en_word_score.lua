local CaseComm = require 'cases/CaseComm'
return {

    {
        name = "ws_en_word_score",
        input = {
            cfg = [==[{
                "appKey": "14255202120000cf",
                "secretKey": "988aaf63008b6db30f38bd60be0c3534",
                "provision": "data/aiengine.provision",
                "deviceId": "03d40274043505adbc06820700080009",
                "prof": {
                    "enable": 1
                },
                "cloud": {
                    "server": "ws://10.0.200.20:8090"
                }
            }
            ]==]
        },
        run = CaseComm.Group_Run,
        cases = {
            "cases/ws/case_en_word_score",
        },
    },

}
