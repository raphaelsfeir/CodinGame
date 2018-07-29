<?php
define('DEBUG', true);
function debug() {if (!DEBUG) return; foreach (func_get_args() as $sArgDebug) error_log(var_export($sArgDebug, true));}
function e($m){echo "$m\n";}
class Partition
{
    public $larg; // Largeur de l'image
    public $haut; // hauteur de l'image
    public $aPic = []; // 0 = pixel blanc ;; 1 = pixel noir ;; (col,row)
    public $aColRef = [];
    public $aColRefC = [];
    public $aRefLines = [];
    public $iThinLine = 0;
    public $iGap = 0;
    public $aNotes = [];
    public function __construct(){
        fscanf(STDIN, "%d %d", $this->w, $this->h);
        $sPic = stream_get_line(STDIN, 6000000, "\n");
        $this->aPic = $this->_transpose($sPic);
    }
    
    private function _transpose($sPic) {
        $aColorsNb = preg_split('#([^ ]* [^ ]*) #', $sPic, -1, PREG_SPLIT_DELIM_CAPTURE | PREG_SPLIT_NO_EMPTY);
        $sBinaryPic = '';
        foreach ($aColorsNb as $sColorNb) {
            list($color, $nb) = explode(' ', $sColorNb);
            $sBinaryPic .= str_repeat(intval($color !== 'W'), $nb);
        }
        $aBinaryPic = array_map('str_split', str_split($sBinaryPic, $this->w));
        array_unshift($aBinaryPic, null);
        return call_user_func_array('array_map', $aBinaryPic);
    }
    
    public function findColRef(){
        foreach ($this->aPic as $nCol => $aCol) {
            if (array_sum($aCol) === 0) {
                unset($this->aPic[$nCol]);
            }
        }
        $this->aColRef = reset($this->aPic);
    }
    
    public function LignesdeRef(){
        $drapeau = false;
        foreach ($this->aColRef as $hP => $vP) {
            if ($drapeau && $vP === '1') {
                ++$this->iThinLine;
            } elseif (!$drapeau && $vP === '1') {
                $this->aRefLines[] = $hP;
                ++$this->iThinLine;
                $drapeau = !$drapeau;
            } elseif ($drapeau && $vP === '0') {
                $drapeau = !$drapeau;
            }
        }
        $this->iThinLine = $this->iThinLine / count($this->aRefLines);
        $this->aRefLines[5] = $this->aRefLines[4] + ($this->aRefLines[4] - $this->aRefLines[3]);
        $this->iGap = $this->aRefLines[1] - $this->aRefLines[0] - $this->iThinLine;
        $this->aColRefC = $this->aColRef;
        for ($i=0; $i<$this->iThinLine; ++$i) {
            $this->aColRefC[$this->aRefLines[5] + $i] = '1';
        }
    }
    
    public function lire(){
        $aNoteActuelle = [];
        $aDiff = [];
        $aColThatDiffIsOnlyTheCLine = range($this->aRefLines[5], $this->aRefLines[5] + $this->iThinLine - 1);
        foreach ($this->aPic as $nCol => $aCol) {
            if ($aCol !== $this->aColRef) {
                $aDiff = array_diff_assoc($aCol, $this->aColRef);
                if ($aColThatDiffIsOnlyTheCLine !== array_keys($aDiff)) {
                    $aNoteActuelle[] = $aDiff;
                    continue;
                }
            }
            if (!empty($aNoteActuelle)) {
                $aAnalyzingNote = $this->_trouveNoteVert($aNoteActuelle);
                $sCurrentNote = $this->_analNote($aAnalyzingNote);
                $this->aNotes[] = $sCurrentNote;
                $aNoteActuelle = [];
            }
        }
        return $this->aNotes;
    }
    
    private function _trouveNoteVert($aCols) {
        foreach ($aCols as $nCol => $aCol) {
            foreach ($aCol as $i => $index) {
                if ($this->aRefLines[5] <= $index && ($this->aRefLines[5] + $this->iThinLine) >= $index) {
                    unset($aCol[$i]);
                }
            }
            if (empty($aCol)) {
                unset($aCols[$nCol]);
            }
        }
        for ($i=0; $i<$this->iThinLine; ++$i) {
            array_shift($aCols);
            array_pop($aCols);
        }
        
        $aAnalyzingNote = $aCols[floor(count($aCols)/2)];
        return $aAnalyzingNote;
    }
    
    private function _analNote($aNote){
        $val = array_keys($aNote);
        $sPitch = $this->_hauteurMusic($val);
        $sTempo = $this->_trouveTempo($val);
        
        return $sPitch . $sTempo;
    }
    
    private function _hauteurMusic($val){
        if (count($val) === 1) {
            return $this->_findPitchSepcial($val[0]);
        }
        
        list($highPoint, $lowPoint) = array(min($val), max($val));
        list($highMiddle, $lowMiddle) = array($highPoint+ceil($this->iGap/2), $lowPoint+ceil($this->iGap/2));
        
        if (
            $lowPoint <= $this->aRefLines[0] || //G1
            ($lowMiddle <= $this->aRefLines[4] && $highMiddle >= $this->aRefLines[3]) //G0
        ) {
            $sNote = 'G';
        } elseif(
            ($lowMiddle <= $this->aRefLines[1] && $highMiddle >= $this->aRefLines[0]) || //F1
            ($lowPoint <= $this->aRefLines[4] && $highPoint >= $this->aRefLines[3]) //F0
        ) {
            $sNote = 'F';
        } elseif(
            ($lowPoint <= $this->aRefLines[1] && $highPoint >= $this->aRefLines[0]) || //E1
            ($lowMiddle <= $this->aRefLines[5] && $highMiddle >= $this->aRefLines[4]) //E0
        ) {
            $sNote = 'E';
        } elseif(
            ($lowMiddle <= $this->aRefLines[2] && $highMiddle >= $this->aRefLines[1]) || //D1
            ($lowPoint <= ($this->aRefLines[5] + $this->iThinLine) && $highPoint >= $this->aRefLines[4]) //D0
        ) {
            $sNote = 'D';
        } elseif(
            ($lowPoint <= $this->aRefLines[2] && $highPoint >= $this->aRefLines[1]) || //C1
            ($lowPoint > ($this->aRefLines[5] + $this->iThinLine) && $highPoint < $this->aRefLines[4]) //C0
        ) {
            $sNote = 'C';
        } elseif($lowMiddle <= $this->aRefLines[3] && $highMiddle >= $this->aRefLines[2]) {
            $sNote = 'B';
        } elseif($lowPoint <= $this->aRefLines[3] && $highPoint >= $this->aRefLines[2]) {
            $sNote = 'A';
        } else {
            $sNote = 'C';
        }
        return $sNote;
    }
    
    private function _findPitchSepcial($index) {
        // Note situé entre 2 lignes
        if ($index < $this->aRefLines[0]) {
            $sNote = 'G';
        } elseif($index < $this->aRefLines[1]) {
            $sNote = 'E';
        } elseif($index < $this->aRefLines[2]) {
            $sNote = 'C';
        } elseif($index < $this->aRefLines[3]) {
            $sNote = 'A';
        } elseif($index < $this->aRefLines[4]) {
            $sNote = 'F';
        } elseif($index < $this->aRefLines[5]) {
            $sNote = 'D';
        } else {
            $sNote = 'C';
        }
        return $sNote;
    }
    
    private function _trouveTempo($val){
        // 1 index => note blanche
        if (count($val) === 1) {
            return 'H';
        }
        
        $start = $val[0];
        for ($i=1, $n=count($val); $i<$n; ++$i) {
            if (++$start !== $val[$i]) {
                if (false === ($iRef = array_search($start, $this->aRefLines))) {
                    // Vide pour une durée courte => note blanche
                    return 'H';
                }
                // Abandon du vide
                $start += $this->iThinLine;
            }
        }
        return 'Q';
    }
}
$oPartition = new Partition();
$aPic = $oPartition->aPic;
$oPartition->findColRef();
$oPartition->LignesdeRef();
$aNotes = $oPartition->lire();
e(implode(' ', $aNotes));
?>
