// Popup kezelése
function showPopup() {
    document.getElementById("popup").style.display = "block";
}

function closePopup() {
    document.getElementById("popup").style.display = "none";
}

// Chart.js diagramok
const inaktivCtx = document.getElementById('chartInaktiv').getContext('2d');
new Chart(inaktivCtx, {
    type: 'doughnut',
    data: {
        labels: ['Aktív kollégisták', 'Több mint 2 hete inaktív'],
        datasets: [{
            data: [180, 20],  // Pl.: 180 aktív, 20 inaktív
            backgroundColor: ['#28A745', '#FF5733']
        }]
    }
});

const szobakCtx = document.getElementById('chartSzobak').getContext('2d');
new Chart(szobakCtx, {
    type: 'doughnut',
    data: {
        labels: ['Foglalt szobák', 'Kiadható szobák'],
        datasets: [{
            data: [45, 15],  // Pl.: 45 foglalt, 15 szabad
            backgroundColor: ['#FFC107', '#17A2B8']
        }]
    }
});

const megteltsegCtx = document.getElementById('chartMegteltseg').getContext('2d');
new Chart(megteltsegCtx, {
    type: 'doughnut',
    data: {
        labels: ['Betöltött helyek', 'Szabad helyek'],
        datasets: [{
            data: [190, 30],  // Pl.: 190 hely betöltve, 30 szabad
            backgroundColor: ['#007BFF', '#CCCCCC']
        }]
    }
});
