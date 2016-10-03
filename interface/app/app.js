angular.module('piInterfaceApp', ['ui.bootstrap'])
    .config(function() {

    })
    .run(function($log, CONFIG) {
        $log.info("PI-INTERFACE VERSION: " + CONFIG.VERSION + " IS RUNNING");
    });
