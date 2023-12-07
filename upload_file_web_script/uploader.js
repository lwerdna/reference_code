function upload()
{
	var input_elem = document.getElementById('file');
	var files = input_elem.files;

	if (files.length != 1)
	{
		console.log("ERROR: expected 1 file");
		return;
	}

	var file = files[0];

	var fd = new FormData();
	fd.append('file', file);
	fetch('cgi-bin/receive.py', { method: 'POST', body: fd }).then(console.log);
}
