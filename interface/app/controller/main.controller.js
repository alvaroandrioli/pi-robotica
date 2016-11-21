angular.module('piInterfaceApp')
    .controller('mainController', function($scope) {
        $scope.states = [];

        $scope.slider = {
            angulo_a: 30,
            angulo_b: 0,
            angulo_c: 35,
            claw: false
        };

        $scope.optionA = {
            floor: 0,
            ceil: 180,
            step: 1
        };

        $scope.optionB = {
            floor: 180,
            ceil: 120,
            step: 1
        };

        $scope.optionC = {
            floor: 0,
            ceil: 50,
            step: 1
        };

        $scope.claw = {
            floor: 0,
            ceil: 1,
            step: 1
        };

        $scope.dataPlot = {
            x: [],
            y: [],
            z: [],
            c: []
        };

        $scope.clearStates = function() {
            $scope.states = [];
        }

        $scope.addState = function() {
            $scope.states.push({
                angulo_a: $scope.slider.angulo_a,
                angulo_b: $scope.slider.angulo_b,
                angulo_c: $scope.slider.angulo_c,
                claw: $scope.slider.claw
            });
        }

        $scope.removeState = function(index) {
            $scope.states.splice(index,1);
            $scope.dataPlot.x.splice(index, 1);
            $scope.dataPlot.y.splice(index, 1);
            $scope.dataPlot.z.splice(index, 1);
            $scope.dataPlot.c.splice(index, 1);
        }

        $scope.addPoint = function() {
            $scope.addState();
            $scope.dataPlot.x.push($scope.slider.angulo_a);
            $scope.dataPlot.y.push($scope.slider.angulo_b);
            $scope.dataPlot.z.push($scope.slider.angulo_c);
            $scope.dataPlot.c.push($scope.slider.claw ? 10 : -10);
        }

        $scope.addLastPoint = function(index) {
            $scope.dataPlot.x.push($scope.states[index].angulo_a);
            $scope.dataPlot.y.push($scope.states[index].angulo_b);
            $scope.dataPlot.z.push($scope.states[index].angulo_c);
            $scope.dataPlot.c.push($scope.states[index].claw);
        }

        $scope.removeLastPoint = function() {
            $scope.dataPlot.x.pop();
            $scope.dataPlot.y.pop();
            $scope.dataPlot.z.pop();
            $scope.dataPlot.c.pop();
        }

        $scope.validateStates = function() {
            return $scope.states.every(function(state) {
                return !state.selected;
            });
        }

        $scope.toggleState = function(index) {
            $scope.states[index]['selected'] = !$scope.states[index].selected;

            if ($scope.states[index]['selected']) {
                $scope.addLastPoint(index   );
            } else {
                $scope.removeLastPoint();
            }
        }

        $scope.parser = function() {
            var res = 'b';

            angular.forEach($scope.states, function(state) {
                res += 's';
                res += normalize(state.angulo_a);
                res += normalize(state.angulo_b);
                res += normalize(state.angulo_c);
                res += (state.claw ? '001' : '000');
                res += 'f';
            })

            res += 'e';

            $scope.stringState = res;
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

        function normalize(number) {
            var temp = String(number);

            if (temp.length == 1)
                temp = '00'+temp;
            if (temp.length == 2)
                temp = '0'+temp;

            return temp;
        }

        $scope.layout = {title: 'Posição do braço'};
        $scope.options = {showLink: false, displayLogo: false, displayModeBar: false};
    });
