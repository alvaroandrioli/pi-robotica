angular.module('piInterfaceApp', ['ui.bootstrap', 'rzModule', 'uiSwitch', 'plotly'])
    .config(function() {

    })
    .run(function($log, CONFIG) {
        $log.info("PI-INTERFACE VERSION: " + CONFIG.VERSION + " IS RUNNING");
    });
