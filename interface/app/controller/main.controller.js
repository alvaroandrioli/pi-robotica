angular.module('piInterfaceApp')
    .controller('mainController', function($scope) {
        $scope.slider = {
            angulo_a: 30,
            angulo_b: 0,
            angulo_c: 35,
            angulo_d: 0,
            claw: false
        };

        $scope.optionA = {
            floor: 30,
            ceil: 40,
            step: 1
        }
        $scope.optionB = {
            floor: 0,
            ceil: 90,
            step: 1
        }
        $scope.optionC = {
            floor: 35,
            ceil: 70,
            step: 1
        }
        $scope.optionD = {
            floor: 0,
            ceil: 1,
            step: 1
        }

        $scope.dataPlot = {
            x: [],
            y: [],
            z: [],
            c: []
        }

        $scope.addPoint = function() {
            $scope.dataPlot.x.push($scope.slider.angulo_a);
            $scope.dataPlot.y.push($scope.slider.angulo_b);
            $scope.dataPlot.z.push($scope.slider.angulo_c);

            if ($scope.dataPlot.x.length <= 1 && $scope.dataPlot.y.length <= 1 && $scope.dataPlot.z.length <= 1 && $scope.dataPlot.c.length <= 1) {
                    if ($scope.slider.claw)
                        //fechado
                        $scope.dataPlot.c.push(5);
                    else
                        //aberto
                        $scope.dataPlot.c.push(-5);
            } else {
                if ($scope.slider.claw)
                    //fechado
                    $scope.dataPlot.c.push(10);
                else
                    //aberto
                    $scope.dataPlot.c.push(-10);
            }


        }

        $scope.data = [{x: $scope.dataPlot.x,
                    y: $scope.dataPlot.y,
                    z: $scope.dataPlot.z,
                    type:'scatter3d',
                    marker: {
                        size: 10,
                        color: $scope.dataPlot.c,
                        cmin: -10,
                        cmax: 10
                    }
                }];

        $scope.layout = {title: 'Posição do braço'};
        $scope.options = {showLink: false, displayLogo: false, displayModeBar: false};
    });
