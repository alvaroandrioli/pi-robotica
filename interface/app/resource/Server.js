angular.module('piInterfaceApp')
    .factory('Server', function(CONFIG, $http) {
        return {
            "sendCode": function(code) {
                return $http.post('http://'+CONFIG.HOST_ADDR+':'+CONFIG.PORT+'/code', {"c": code});
            }
        }
    });
