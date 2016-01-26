Faster, Lighter, Cleaner - Phos
===============================

Tonight, I put some effort into creating a minimal distribution of <a href="data:application/javascript,////////////////////////////////////////////////////////////////////////////////////////////////////%0A//%20Phos%0A//%0A//%20%A9%202009%2C%202010%2C%202011%20David%20J.%20Goehrig%20%3Cdave@nexttolast.com%3E%0A//%20%0A//%20%20%20%20This%20program%20is%20free%20software%3A%20you%20can%20redistribute%20it%20and/or%20modify%0A//%20%20%20%20it%20under%20the%20terms%20of%20the%20GNU%20General%20Public%20License%20as%20published%20by%0A//%20%20%20%20the%20Free%20Software%20Foundation%2C%20either%20version%203%20of%20the%20License%2C%20or%0A//%20%20%20%20%28at%20your%20option%29%20any%20later%20version.%0A//%0A//%20%20%20%20This%20program%20is%20distributed%20in%20the%20hope%20that%20it%20will%20be%20useful%2C%0A//%20%20%20%20but%20WITHOUT%20ANY%20WARRANTY%3B%20without%20even%20the%20implied%20warranty%20of%0A//%20%20%20%20MERCHANTABILITY%20or%20FITNESS%20FOR%20A%20PARTICULAR%20PURPOSE.%20%20See%20the%0A//%20%20%20%20GNU%20General%20Public%20License%20for%20more%20details.%0A//%0A//%20%20%20%20You%20should%20have%20received%20a%20copy%20of%20the%20GNU%20General%20Public%20License%0A//%20%20%20%20along%20with%20this%20program.%20%20If%20not%2C%20see%20%3Chttp%3A//www.gnu.org/licenses/%3E.%0A//%0A////////////////////////////////////////////////////////////////////////////////////////////////////%0A%0AObject.prototype.a%20%3D%20Object.prototype.an%20%3D%20function%28x%2Cv%29%20%7B%20%0A%09return%20x.can%28%27init%27%29%20%3F%20x.clone%28%29.init%28v%29%3A%20x.clone%28%29%20%0A%7D%3B%0A%0A//%20Constructor%20Global%0AA%20%3D%20An%20%3D%20%7B%0A%09object%3A%20function%28%29%20%7B%20return%20a%28%7B%7D%29%20%7D%2C%0A%09string%3A%20function%28%29%20%7B%20return%20a%28%27%27%29%20%7D%2C%0A%09array%3A%20function%28%29%20%7B%20return%20a%28%5B%5D%29%20%7D%2C%0A%7D%3B%0A%0AObject.prototype.the%20%3D%20function%28x%29%20%7B%20return%20x%20%7D%3B%0A%0A//%20Singletons%0AThe%20%3D%20%7B%7D%3B%0A%0AObject.prototype.value%20%3D%20function%28%29%20%7B%20return%20this%3B%20%7D%0A%0AObject.prototype.clone%20%3D%20function%28%29%20%7B%0A%09var%20Proto%20%3D%20function%28%29%20%7B%7D%3B%0A%09Proto.prototype%20%3D%20this%3B%0A%09return%20new%20Proto%28%29%20%0A%7D%0A%0AObject.prototype.copy%20%3D%20function%28o%29%20%7B%0A%09var%20me%20%3D%20this%3B%0A%09o.each%28function%28v%2Ck%29%20%7B%20me%5Bk%5D%20%3D%20v%20%7D%29%3B%0A%09return%20this%20%0A%7D%0A%0AObject.prototype.does%20%3D%20function%28v%2Cf%29%20%7B%20this%5Bv%5D%20%3D%20f%3B%20return%20this%20%7D%0A%0AString.prototype.capitalize%20%3D%20function%28%29%20%7B%20return%20this.toString%28%29%5B0%5D.toUpperCase%28%29%20+%20this.substr%281%29%20%7D%0A%0AObject.prototype.has%20%3D%20function%28%29%20%7B%0A%09var%20me%20%3D%20this%3B%0A%09for%20%28%20var%20i%20%3D%200%3B%20i%20%3C%20arguments.length%3B%20++i%29%20%20%7B%0A%09%09%28function%28name%29%20%7B%0A%09%09%09var%20prop%20%3D%20name.capitalize%28%29%3B%0A%09%09%09me%5Bname%5D%20%3D%20function%28%29%20%7B%0A%09%09%09%09if%20%28arguments.length%29%20%7B%20me%5Bprop%5D%20%3D%20arguments%5B0%5D%3B%20return%20me%20%7D%0A%09%09%09%09return%20me%5Bprop%5D%0A%09%09%09%7D%3B%0A%09%09%7D%29%28arguments%5Bi%5D%29%3B%0A%09%7D%0A%09return%20me%3B%0A%7D%0A%0AObject.prototype.from%20%3D%20function%28%29%20%7B%0A%09this%5B%27init%27%5D%20%3D%20function%28%29%20%7B%20return%20this%20%7D%3B%0A%09for%20%28var%20i%20%3D%200%3B%20i%20%3C%20arguments.length%3B%20++i%29%20this.copy%28arguments%5Bi%5D%29%3B%0A%09return%20this%20%0A%7D%0A%0AObject.prototype.contains%20%3D%20function%28e%29%20%7B%0A%09var%20retval%20%3D%20false%3B%0A%09this.each%28function%28v%2Ck%29%20%7B%20if%20%28k%20%3D%3D%20e%29%20return%20retval%20%3D%20true%20%7D%29%3B%0A%09return%20retval%20%0A%7D%0A%0AObject.prototype.owns%20%3D%20function%28k%29%20%20%7B%0A%09return%20this.hasOwnProperty%28k%29%0A%7D%0A%0AObject.prototype.each%20%3D%20function%28f%29%20%7B%0A%09for%20%28var%20k%20in%20this%29%20if%20%28this.owns%28k%29%20%26%26%20k%20%21%3D%20%27prototype%27%29%20f%28this%5Bk%5D%2Ck%29%3B%0A%09return%20this%20%0A%7D%0A%0AObject.prototype.all%20%3D%20function%28f%29%20%7B%0A%09for%20%28var%20k%20in%20this%29%20if%20%28k%20%21%3D%20%27prototype%27%29%20f%28this%5Bk%5D%2Ck%29%3B%0A%09return%20this%20%0A%7D%0A%0AObject.prototype.which%20%3D%20function%28f%29%20%7B%0A%09var%20w%20%3D%20%5B%5D%3B%0A%09this.each%28function%28v%2Ck%29%20%7B%20if%20%28f%28v%2Ck%29%29%20w.push%28v%29%20%7D%29%3B%0A%09return%20w%20%0A%7D%0A%0AObject.prototype.can%20%3D%20function%28k%29%20%7B%20return%20%28typeof%28this%5Bk%5D%29%20%3D%3D%20%22function%22%29%20%7D%0A%0AObject.prototype.slots%20%3D%20function%28%29%20%7B%0A%09var%20i%20%3D%200%3B%0A%09this.each%28function%28v%2Ck%29%20%7B%20if%20%28k%20%26%26%20v%29%20++i%20%7D%29%3B%0A%09return%20i%20%0A%7D%0A%0AObject.prototype.its%20%3D%20function%28k%29%20%7B%20return%20k.last%28%29%20%21%3D%20%27*%27%20%3F%20this%5Bk.append%28%27*%27%29%5D%20%3A%20this%5Bk%5D%20%7D%0A%0AObject.prototype.of%20%3D%20function%28x%2Ck%29%20%7B%20%0A%09var%20args%20%3D%20%5B%20arguments%5B1%5D%2C%20arguments%5B2%5D%2C%20arguments%5B3%5D%2C%20arguments%5B4%5D%2C%20arguments%5B5%5D%20%5D%3B%0A%09var%20me%20%3D%20this%3B%0A%09x.parts%28%29.every%28function%28p%2Ci%29%20%7B%20if%20%28p.is%28me%29%20%26%26%20p.can%28k%29%29%20p%5Bk%5D%28args%5B1%5D%2Cargs%5B2%5D%2Cargs%5B3%5D%2Cargs%5B4%5D%29%7D%29%3B%0A%09return%20this%20%0A%7D%0A%0AObject.prototype.names%20%3D%20function%28%29%20%7B%0A%09var%20retval%20%3D%20%5B%5D%3B%0A%09var%20me%20%3D%20this%3B%0A%09window.each%28function%28v%2Ck%29%20%7B%20if%20%28v%20%3D%3D%3D%20me%29%20retval.push%28k%29%20%7D%29%3B%0A%09return%20retval%20%0A%7D%0A%0AObject.prototype.name%20%3D%20function%28%29%20%7B%20return%20this.names%28%29%5B0%5D%20%7D%0AObject.prototype.plural%20%3D%20function%28x%29%20%7B%20return%20window%5Bx%5D%20%3D%20this%20%7D%0A%0AObject.prototype.named%20%3D%20%20function%28x%29%20%7B%0A%09var%20lc%20%3D%20x.name%28%29.toLowerCase%28%29%3B%0A%09var%20me%20%3D%20this%3B%0A%09An%5Blc%5D%3D%20function%28y%29%20%7B%20return%20a%28me%2Cy%29%20%7D%3B%0A%09return%20window%5Bx.name%28%29%5D%20%3D%20this%20%0A%7D%0A%0AObject.prototype.is%20%3D%20function%28x%29%20%7B%0A%09var%20me%20%3D%20this%3B%0A%09var%20retval%20%3D%20true%3B%0A%09x.all%28function%28v%2Ck%29%20%7B%20if%20%28x.can%28k%29%20%26%26%20%21me.can%28k%29%29%20return%20retval%20%3D%20false%20%7D%29%3B%0A%09return%20retval%20%0A%7D%0A%0AObject.prototype.implements%20%3D%20function%28%29%20%7B%0A%09var%20me%20%3D%20this%3B%0A%09var%20retval%20%3D%20%5B%5D%3B%0A%09Objects.each%28function%28v%2Ck%29%20%7B%20if%20%28me.is%28v%29%29%20retval.push%28k%29%20%7D%29%3B%0A%09return%20retval%20%0A%7D%0A%0AObject.prototype.any%20%3D%20function%28f%29%20%7B%0A%09var%20retval%20%3D%20null%3B%0A%09this.each%28function%28v%2Ck%29%20%7B%20if%20%28f%28v%2Ck%29%29%20return%20retval%20%3D%20v%20%7D%29%3B%0A%09return%20retval%3B%0A%7D%0A%0AObject.prototype.module%20%3D%20function%28%29%20%7B%0A%09var%20ots%20%3D%20Object.prototype.toString%3B%0A%09Object.prototype.toString%20%3D%20function%28%29%20%7B%0A%09%09var%20retval%20%3D%20%27%7B%20%27%3B%0A%09%09this.each%28function%28v%2Ck%29%20%7B%20%0A%09%09%09if%20%28typeof%28v%29%20%3D%3D%20%27function%27%29%20retval%20%3D%20retval.append%28k%2C%27%3A%20%27%2Cv%2C%27%2C%20%27%29%3B%20%0A%09%09%09if%20%28typeof%28v%29%20%3D%3D%20%27string%27%29%20retval%20%3D%20retval.append%28k%2C%27%3A%20%22%27%2C%20v%2C%20%27%22%2C%20%27%29%3B%0A%09%09%09if%20%28typeof%28v%29%20%3D%3D%20%27number%27%29%20retval%20%3D%20retval.append%28k%2C%27%3A%20%27%2C%20v%2C%20%27%2C%20%27%29%3B%0A%09%09%09if%20%28typeof%28v%29%20%3D%3D%20%27boolean%27%29%20retval%20%3D%20retval.append%28k%2C%27%3A%20%27%2C%20v%2C%20%27%2C%20%27%29%3B%0A%09%09%09if%20%28typeof%28v%29%20%3D%3D%20%27object%27%20%26%26%20v.can%28%27every%27%29%29%20%0A%09%09%09%09retval%20%3D%20retval.append%28k%2C%20%27%3A%20%5B%27%2C%20v.join%28%27%2C%27%29%20%2C%20%27%5D%2C%20%27%29%3B%0A%09%09%09if%20%28typeof%28v%29%20%3D%3D%20%27object%27%29%20retval%20%3D%20retval.append%28k%2C%20%27%3A%20%27%2C%20v.name%28%29%2C%20%27%2C%20%27%29%3B%0A%09%09%7D%29%3B%0A%09%09return%20retval.append%28%27%7D%27%29%20%7D%3B%0A%09var%20retval%20%3D%20%27function%28%29%20%7B%20return%20%27.append%28%20this.toString%28%29%2C%20%27%20%7D%27%29%3B%0A%09Object.prototype.toString%20%3D%20ots%3B%0A%09return%20retval%20%0A%7D%0A%0AObject.prototype.use%20%3D%20function%28%29%20%7B%0A%09var%20modules%20%3D%20%5B%5D%3B%0A%09modules.push.apply%28modules%2Carguments%29%3B%0A%09var%20module%20%3D%20modules.shift%28%29%3B%0A%09var%20url%20%3D%20document.location.append%28module%29%3B%0A%09var%20cb%20%3D%20function%28txt%29%20%7B%0A%09%09if%20%28%21txt%29%20alert%28%27Failed%20to%20load%20%27.append%28url%29%29%3B%0A%09%09try%20%7B%20%0A%09%09%09eval%28%27%28%20function%20%28%29%20%7B%20%27.append%28txt%2C%27%20%7D%20%29%27%29%29%28%29%3B%20%0A%09%09%7D%20catch%28e%29%20%7B%20alert%28%27Load%20error%3A%20%27.append%28e%2C%27%3A%27%2Ctxt%29%29%20%7D%0A%09%09if%20%28modules.length%20%3E%200%20%29%20%7B%0A%09%09%09var%20module%20%3D%20modules.shift%28%29%3B%0A%09%09%09var%20url%20%3D%20document.location.append%28module%29%3B%0A%09%09%09url.get%28cb%29%3B%0A%09%09%7D%0A%09%7D%3B%0A%09return%20url.get%28cb%29%20%0A%7D%0A%09%0AObject.prototype.download%20%3D%20function%28%29%20%7B%0A%09document.location.href%20%3D%20%22data%3Aapplication/javascript%2C%22.append%28this.toString%28%29.encode%28%29%29%3B%0A%09return%20this%3B%0A%7D%0A%0AObject.prototype.when%20%3D%20HTMLElement.prototype.when%20%3D%20function%28e%2Cf%29%20%7B%0A%09this.addEventListener%28e%2Cf%2Cfalse%29%3B%0A%09return%20this%3B%0A%7D%0A%0A%0A%0AArray.prototype.every%20%3D%20function%28f%29%20%7B%0A%09for%20%28var%20i%20%3D%200%3B%20i%20%3C%20this.length%3B%20++i%29%20f%28this%5Bi%5D%2Ci%29%3B%0A%09return%20this%3B%0A%7D%0A%0AArray.prototype.map%20%3D%20function%28f%29%20%7B%0A%09var%20retval%20%3D%20%5B%5D%3B%0A%09this.every%28function%28x%2Ci%29%20%7B%20retval.push%28f%28x%29%29%20%7D%29%3B%0A%09return%20retval%3B%0A%7D%0A%0AArray.prototype.apply%20%3D%20function%28f%2Co%29%20%7B%0A%09var%20retval%20%3D%20o%3B%0A%09this.every%28function%28x%2Ci%29%20%7B%20retval%20%3D%20f%28retval%2Cx%29%20%7D%29%3B%0A%09return%20retval%3B%0A%7D%0A%09%0AArray.prototype.contains%20%3D%20function%28e%29%20%7B%0A%09var%20retval%20%3D%20false%3B%0A%09this.every%28function%28x%2Ci%29%20%7B%20if%20%28x%20%3D%3D%20e%29%20return%20retval%20%3D%20true%20%7D%29%3B%0A%09return%20retval%3B%0A%7D%0A%0AArray.prototype.append%20%3D%20function%28a%29%20%7B%0A%09this.push.apply%28this%2Ca%29%3B%0A%09return%20this%0A%7D%0A%0AArray.prototype.and%20%3D%20function%28%29%20%7B%0A%09this.push.apply%28this%2Carguments%29%3B%0A%09return%20this%0A%7D%0A%0AArray.prototype.except%20%3D%20function%20%28e%29%20%7B%20%0A%09for%20%28var%20i%20%3D%200%3B%20i%20%3C%20this.length%3B%20++i%29%20if%20%28this%5Bi%5D%20%3D%3D%20e%29%20this.splice%28i%2C1%29%3B%09%0A%7D%0A%0AArray.prototype.join%20%3D%20function%28s%29%20%7B%0A%09var%20retval%20%3D%20%27%27%3B%0A%09for%20%28var%20i%20%3D%200%3B%20i%20%3C%20this.length%20-%201%3B%20++i%29%20retval%20+%3D%20this%5Bi%5D%20+%20s%3B%0A%09return%20retval%20+%20this%5Bi%5D%3B%0A%7D%0A%0A%0AString.prototype.last%20%3D%20function%28%29%20%7B%20%0A%09return%20this.substring%28this.length-1%29%20%0A%7D%0A%0AString.prototype.first%20%3D%20function%28%29%20%7B%20%0A%09return%20this.substring%280%2C1%29%20%0A%7D%0A%0AString.prototype.decode%20%3D%20function%28%29%20%7B%20%0A%09return%20unescape%28this%29%20%0A%7D%0A%0AString.prototype.encode%20%3D%20function%28%29%20%7B%20%0A%09return%20escape%28this%29%20%0A%7D%0A%0AString.prototype.append%20%3D%20function%28%29%20%7B%0A%09var%20retval%20%3D%20this%3B%0A%09for%20%28var%20i%20%3D%200%3B%20i%20%3C%20arguments.length%3B%20++i%29%20retval%20+%3D%20arguments%5Bi%5D.toString%28%29%3B%0A%09return%20retval%20%0A%7D%0A%0AString.prototype.contains%20%3D%20function%28s%29%20%7B%20%0A%09return%200%20%3C%3D%20this.indexOf%28s%29%20%0A%7D%0A%0AString.prototype.name%20%3D%20function%28%29%20%7B%20%0A%09return%20this%20%0A%7D%0A%0AString.prototype.join%20%3D%20function%28%29%20%7B%0A%09var%20retval%20%3D%20%27%27%3B%0A%09for%20%28var%20i%20%3D%200%3B%20i%20%3C%20arguments.length%20-%201%3B%20++i%29%20retval%20+%3D%20arguments%5Bi%5D%20+%20this%3B%0A%09return%20retval%20+%20arguments%5Bi%5D%3B%0A%7D%0A%0AString.prototype.request%20%3D%20function%28method%2Ccb%2Cdata%29%20%7B%0A%09var%20_request%20%3D%20XMLHttpRequest%20%3F%20new%20XMLHttpRequest%28%29%3A%20_doc.createRequest%28%29%3B%0A%09_request.onreadystatechange%20%3D%20function%20%28%29%20%7B%0A%09%09if%20%28this.readyState%20%21%3D%204%20%7C%7C%20typeof%28cb%29%20%21%3D%20%22function%22%29%20return%3B%0A%09%09if%20%28this.status%20%3D%3D%20404%29%20cb%28null%29%3B%0A%09%09if%20%28this.status%20%3D%3D%20200%29%20cb%28this.responseText%29%3B%0A%09%7D%3B%0A%09_request.open%28method%2Cthis%2Ctrue%29%3B%0A%09_request.setRequestHeader%28%27Content-Type%27%2C%27text/plain%27%29%3B%0A%09_request.send%28data%20%3F%20data%20%3A%20%27%27%29%3B%0A%09return%20this%3B%0A%7D%0A%0AString.prototype.get%20%3D%20function%28cb%2Cdata%29%20%7B%20return%20this.request%28%22GET%22%2Ccb%29%20%7D%0AString.prototype.post%20%3D%20function%28cb%2Cdata%29%20%7B%20return%20this.request%28%22POST%22%2Ccb%2Cdata%29%20%7D%0AString.prototype.put%20%3D%20function%28cb%2Cdata%29%20%7B%20return%20this.request%28%22PUT%22%2Ccb%2Cdata%29%20%7D%0AString.prototype.delete%20%3D%20function%28cb%2Cdata%29%20%7B%20return%20this.request%28%22DELETE%22%2Ccb%29%20%7D%0A%0A%0A//%20stuff.js%0A//%0A//%20Single%20Transfer%20Utility%20For%20Files%0A//%0A%0AAn.object%28%29.named%28%27Stuff%27%29.%0A%09has%28%27files%27%2C%27then%27%29.%0A%09does%28%27path%27%2Cfunction%28%29%20%7B%0A%09%09var%20url%20%3D%20document.location.toString%28%29%3B%0A%09%09for%20%28var%20i%20%3D%20url.length-1%3B%20i%3B%20--i%29%20if%20%28url%5Bi%5D%20%3D%3D%20%27/%27%29%20break%3B%0A%09%09return%20url.substr%280%2Ci+1%29%3B%0A%09%7D%29.%0A%09does%28%27pack%27%2Cfunction%28%29%20%7B%0A%09%09var%20me%20%3D%20this%3B%0A%09%09me.files%28%5B%5D%29%3B%0A%09%09var%20files%20%3D%20%5B%5D%3B%0A%09%09files.push.apply%28files%2Carguments%29%3B%0A%09%09var%20name%20%3D%20files.shift%28%29%3B%0A%09%09var%20cb%20%3D%20function%28resp%29%20%7B%0A%09%09%09me.files%28%29.push%28resp%29%3B%09%0A%09%09%09files.length%20%3F%20me.path%28%29.append%28files.shift%28%29%29.get%28cb%29%3A%0A%09%09%09%09%28me.then%28%29%29%28%29%3B%0A%09%09%7D%3B%0A%09%09me.path%28%29.append%28name%29.get%28cb%29%3B%0A%09%09return%20me%3B%0A%09%7D%29.%0A%09does%28%27dump%27%2Cfunction%28%29%20%7B%0A%09%09return%20this.files%28%29.join%28%22%5Cn%22%29%3B%0A%09%7D%29%0A%0A">Phos</a>.  If your web browser supports data: URIs, and all adequate browsers these days do, just click it.  Or better yet copy the link and use as the src="" attribute of your script tag.<br /><br />As part of my on going effort to make Phos something usable for building real world web applications, I&#39;ve started writing a bundling tool that I call <span style="font-weight:italic;">Stuff</span>, which is short for Single Transport Utility For Files.  Basically, it is a way to bundle a bunch of crap in a single data URL or as a bundle file consisting of data URLs that can be embedded in a page for distribution, or included in a page via an object tag.  This object is a good sample to look at to see the programming style embrace by Phos, and how it extends the language into something rather beautiful:<br /><blockquote><br /><pre><br />// stuff.js<br />//<br />// Single Transfer Utility For Files<br />//<br /><br />An.object().named(&#39;Stuff&#39;).<br />       has(&#39;files&#39;,&#39;then&#39;).<br />       does(&#39;path&#39;,function() {<br />               var url = document.location.toString();<br />               for (var i = url.length-1; i; --i) if (url[i] == &#39;/&#39;) break;<br />               return url.substr(0,i+1);<br />       }).<br />       does(&#39;pack&#39;,function() {<br />               var me = this;<br />               me.files([]);<br />               var files = [];<br />               files.push.apply(files,arguments);<br />               var name = files.shift();<br />               var cb = function(resp) {<br />                       me.files().push(resp);<br />                       files.length ? me.path().append(files.shift()).get(cb):<br />                               (me.then())();<br />               };<br />               me.path().append(name).get(cb);<br />               return me;<br />       }).<br />       does(&#39;dump&#39;,function() {<br />               return this.files().join("\\n");<br />       })<br /></pre><br /></blockquote><br /><br />The way that Phos works is it extends the base semantics of the language by augmenting the vocabulary associated with the core objects.  The word <span style="font-style:italic;">An</span> ( and its sister <span style="font-style:italic;">A</span> ) is a global that encapsulates all of the factory methods for every <span style="font-weight:bold;">archetype</span>.  As Phos uses prototypal inheritance and the occasional bit of shallow copying, this makes for a very clean interface.  The method <span style="font-style:italic;">object()</span> instantiates a new object, descending from <span style="font-weight:bold;">Object</span> itself, and is just one such constructor.  The <span style="font-style:italic;">named()</span> method extends <span style="font-weight:bold;">Object</span> and creates a new <span style="font-weight:bold;">well named</span> archetype, creates a generic constructor in <span style="font-style:italic;">A and An</span>, and sets the specified global variable, in this case <span style="font-style:italic;">Stuff</span>.<br /><br />The ending of each line with a <span style="font-weight:bold;">period</span> is a conscious stylistic choice, as most code is a chain of method invocations, one after the other.  These run on sentences require some visual demarcation, as they are actually single statements.  Since these statements almost always end on the last line of the file, I usually just avoid the final semi-colon, as they will be auto-inserted by the grammar rules anyways.<br /><br />The <span style="font-style:italic;">has()</span> method is another extension to <span style="font-weight:bold;">Object</span> which takes a variable number of strings and then generates both an accessor function, and a named internal property of the object for each.  The convention here is that all methods begin with a lower cased letter, and their associated property begins with an uppercase one.  As the programming idiom is one of behavioralism, it is generally frowned upon to actually ever invoke the underlying property.  This is especially true when using any of the extended Phos library, as most methods get overridden in child objects many times over.<br /><br /><blockquote><br /><pre><br />Object.prototype.has = function() {<br /> var me = this;<br /> for ( var i = 0; i < arguments.length; ++i)  {<br />  (function(name) {<br />   var prop = name.capitalize();<br />   me[name] = function() {<br />    if (arguments.length) { me[prop] = arguments[0]; return me }<br />    return me[prop]<br />   };<br />  })(arguments[i]);<br /> }<br /> return me;<br />}<br /></pre><br /></blockquote><br /><br />This method internally uses a closure to capture both the context and a second closure to capture the computed property name.  It also highlights the fact that I hate typing <span style="font-weight:bold;">this</span>, which probably comes from groking <a href="http://selflanguage.org">Self</a>.  This idiom of having functions which perform different tasks depending on how they are called is also a critical piece of the Phos design strategy, as the meaning of all words is contextual.  The more contextually aware your methods and objects are, the easier it is to ensure the correct behavior at any particular point in time.<br /><br />The final set of chained <span style="font-style:italic;">does()</span> methods simply encapsulates the assignment / binding in a fashion more reminiscent of LISP let binding.  This also makes it possible to expand the semantics of method definitions in the future to include other bits of information that I haven&#39;t thought of yet.  But mostly, it adds a beautiful consistency to the definition of an <span style="font-weight:bold;">archetypal object</span> as a series of transformations on some preexisting entity.  <br /><br />Each component in this framework is context dependent, in that there is a strict order by which these transformation must be defined to retain meaning.  But that problem is solved by having tools that make maintaining those orderings trivial:<br /><br /><blockquote><br /><pre><br />        Stuff.pack( &#39;Object&#39;,&#39;Array&#39;,&#39;String&#39;, &#39;Stuff&#39; ).<br />        then(function () { Stuff.dump().download() });<br /></pre><br /></blockquote><br /><br />This is the script I used to create the minimal Phos data URI in the link above, and shows how the <span style="font-style:italic;">Stuff</span> object is used.  Here I&#39;m using the archetype as a singleton, but you could just as easily instantiate more than one.  You&#39;ll notice that the <span style="font-style:italic;">then()</span> accessor is used to register a callback that is invoked after all of the <span style="font-style:italic;">pack()</span> files have been downloaded via XHR.  This <span style="font-weight:bold;">then</span> idiom is incredibly powerful when programming in a callback driven application.    I will probably add more support for that into the base function object eventually, having the ability to append chains of continuations to any function, so that you can express the future state of the program as a sequence of transformations upon the object itself.<br /><br />Probably the final bit of code to note is the XHR code itself is attached to the <span style="font-weight:bold;">String</span> object, as it allows us to do full REST style calls by calling the <span style="font-style:italic;">.get(), .put(), .post(),</span> and <span style="font-style:italic;">.delete()</span> methods on a url.   You can see that in the <span style="font-weight:bold;">Stuff</span> code which appends a file name to the current document&#39;s path and then just gets it.  This makes working with a REST api for a key value store like <a href="http://basho.com/riaksearch.html">Riak</a> incredibly easy to use.<br /><br />My next steps are going to be to marry the progress on PhosGL with the 2D Phos code base so that I&#39;m back down to only one.  Using the new <span style="font-weight:bold;">Stuff</span> mechanism to generate releases, I can trivially build a tool for rolling your own subset of a release.  I am also planning on extending <span style="font-weight:bold;">Stuff</span> to allow for creating entire stand alone applications which can be embedded in a web page via the &lt;object&gt; tag.  Since each embedded object gets its own window context, and can not be manipulated by (or manipulate) the surrounding page context, there&#39;s no danger of crushing other popular web frameworks.